
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Location.h"
#include "LocationList.h"
#include "CampusLocation.h"
#include "CityLocation.h"

using namespace std;

LocationList::LocationList() {
    list = vector<Location*>();
}

LocationList::~LocationList() {
    for (int i = 0; i < list.size(); i++) {
        delete list[i];
    }
}

void LocationList::AddLocation(Location* new_loc) {
    list.push_back(new_loc);
}

void LocationList::FromFile(std::string fname) {
    ifstream infile;
    infile.open(fname);
    if (infile.good()) {
        for (int i = 0; i < list.size(); i++) {
            delete list[i];
        }
        list.clear();

        string next_line;
        Location* next_loc;

        getline(infile, next_line);
        int num_locs = stoi(next_line);
        for (int i = 0; i < num_locs; i++) {
            getline(infile, next_line);
            if (next_line == "campuslocation")
                next_loc = new CampusLocation();
            else
                next_loc = new CityLocation();
            next_loc->Read(infile);
            AddLocation(next_loc);
        }
    }
    infile.close();
}

void LocationList::ToFile(std::string fname) {
    ofstream outfile;
    outfile.open(fname);
    if (outfile.good()) {
        outfile << list.size() << endl;
        for (int i = 0; i < list.size(); i++) {
            list[i]->Write(outfile);
        }
    }
    outfile.close();
}

void LocationList::Sort(Position p){
    sort(list.begin(),list.end(),Closer(p));
}
