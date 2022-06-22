
#include <iostream>
#include "CityLocation.h"

using namespace std;

bool CityLocation::Reserve() {
    if (reservations > 0) {
        reservations--;
        return true;
    }
    return false;
}

void CityLocation::Print() const {
    cout << "*** Off-Campus ***" << endl
         << "Location:     " << name    << endl
         << "Address:      " << address << endl
         << "Hours:        " << hours   << endl
         << "Reservations: " << reservations << endl;
}

void CityLocation::Read(std::istream& s) {
    string x,y;
    getline(s, name, ',');
    while (s.peek() == ' ') { s.get(); }
    getline(s, address, ',');
    while (s.peek() == ' ') { s.get(); }
    getline(s, hours, ',');
    while (s.peek() == ' ') {s.get();}
    getline(s,x,',');
    while (s.peek() == ' ') {s.get();}
    getline(s,y,','); 
    pos = Position(stof(x),stof(y));
    s >> reservations;
    while (s.peek() == '\n') { s.get(); }
}

void CityLocation::Write(std::ostream& s) const {
    int x = pos.GetX();
    int y = pos.GetY();
    s << "citylocation" << endl;
    s << name << "," << address << "," << hours << "," << x << ","<< y << "," << reservations;
}

Location* CityLocation::Clone() { return new CityLocation(name, address, hours, reservations); }
