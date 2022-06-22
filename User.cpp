
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Position.h"
#include "User.h"

using namespace std;

void User::_ReadPositions(const std::string fname) {
    float next_x, next_y;
    ifstream positions_file;

    positions_file.open(fname);
    if (positions_file.good()) {
        positions.clear(); // empty the old positions before reading the new ones.
        // we will go until we've read 24 hours of data, but its a good idea to also check we didn't reach end of file early.
        while (positions.size() <= 24 && !positions_file.eof()) {
            positions_file >> next_x >> next_y;
            positions.emplace_back(next_x, next_y); // vector lets us construct the Position object in place with emplace_back.
        }
    }
    positions_file.close();
}

void User::SetLast(const std::string new_last) {
    l_name = new_last;
    user_filename = l_name + ".txt";
    reservations_filename = l_name + "_reservations.txt";
}

void User::SetUnits(bool set_metric) {
// only try to change if there's a change to make.
    if (is_metric != set_metric) {
        if (set_metric) {
            // If we're going to metric, divide imperial by conversion factor.
            height /= 3.28;
            weight /= 2.20;
        }
        else {
            // If we're going to imperial, multiply metric by conversion factor.
            height *= 3.28;
            weight *= 2.20;
        }
        is_metric = set_metric;
    }
}

void User::MakeReservation(Location* reserve) {
    if (reserve->IsReservable()) {
        // Use clone function so the reservation here doesn't have same location as in master list - avoids double-deletion.
        reservations.AddLocation(reserve->Clone());
    }
}

int User::CheckExposures() const {
    int num_exposures = 0;

    typedef vector<vector<Position>> Database; // rename vector<vector<Position>> to something simpler.
    // recall, earlier in the semester, we noted that functions can have static variables.
    // we'll use this feature to ensure we only need to read the database once.
    static Database db = Database(); 
    // set up other variables
    float next_x, next_y;
    int num_people;
    string dummy;
    ifstream database_file;

    // if we didn't do it already, read the database.
    if (db.empty()) {
        //cout << "Reading databases.txt...";
        database_file.open("databases.txt");
        if (database_file.good()) {
            database_file >> num_people;
            for (int person = 0; person < num_people; person++) {
                db.emplace_back(); // we need to make the next 'row', vector lets us construct the vector<Position> at this index with emplace_back.
                for (int hour = 0; hour < 24; hour++) {
                    database_file >> next_x >> next_y;
                    db[person].emplace_back(next_x, next_y); // vector lets us construct the Position object in place with emplace_back.
                }
                getline(database_file, dummy); // ignore the rest of the last line.
                getline(database_file, dummy); // ignore ***
            }
        }
        database_file.close();
        //cout << " Done." << endl;
    }
    for (int person = 0; person < db.size(); person++) {
        for (int hour = 0; hour < 24; hour++) {
            if (positions[hour] - db[person][hour] < 6.0) {
                num_exposures++;
                break; // if we found an exposure from current person, no need to keep looking at that person's positions.
            }
        }
    }
    return num_exposures;
}

void User::PrintData() const {
   cout << "Your data:" << endl
        << "Name:   " << to_string() << endl
        << "Age:    " << age << endl
        << "Height: " << height << " " << (is_metric ? "m" : "ft" ) << endl
        << "Weight: " << weight << " " << (is_metric ? "kg": "lbs") << endl
        << "Press enter to return to menu.";
}

void User::PrintReservations() const {
    cout << "Here are your reservations:" << endl;
    for (int i = 0; i < reservations.GetCount(); i++) {
        reservations.GetLocation(i)->Print();
    cout << "Press enter to return to menu." << endl;
    }
}

void User::Read(bool& is_imperial, std::string fname) {
    ifstream user_file, positions_file;

    if (fname != "") {
        int i = 0;
        while(fname[i] != '.') i++; // find the '.' in the filename, so we can get the part with just the name.
        string r_fname = fname.substr(0,i) + "_reservations.txt";
        string p_fname = fname.substr(0,i) + "_positions.txt";

        user_file.open(fname);
        reservations.FromFile(r_fname);
        _ReadPositions(p_fname);
    }
    else {
        user_file.open(user_filename);
        reservations.FromFile(reservations_filename);
        _ReadPositions(positions_filename);
    }
    if (user_file.good()) {
        user_file >> f_name >> l_name >> age >> height >> weight >> is_imperial;
        is_metric = !is_imperial;
        // after loading a user, we need to update the filenames.
        user_filename = l_name + ".txt";
        reservations_filename = l_name + "_reservations.txt";
        positions_filename = l_name + "_positions.txt";
    }
    user_file.close();
}

void User::Write(const bool is_imperial) {
    ofstream user_file;

    user_file.open(user_filename);
    if (user_file.good()) {
        user_file << f_name << " " << l_name << " " << age << " " << height << " " << weight << " " << is_imperial;
        reservations.ToFile(reservations_filename);
    }
    user_file.close();
}

Position User:: AveragePosition() const{
    Position i = accumulate(positions.begin(),positions.end(),Position(0,0));
    return i/24.0;
}