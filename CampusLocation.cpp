#include <iostream>
#include "CampusLocation.h"

using namespace std;

bool CampusLocation::Reserve() {
    return false;
}

void CampusLocation::Print() const {
    cout << "*** On-Campus ***" << endl
         << "Location:     " << name    << endl
         << "Address:      " << address << endl
         << "Hours:        " << hours   << endl
         << "Reservations: None" << endl;
         
}

void CampusLocation::Read(std::istream& s) {
    getline(s, name, ',');
    while (s.peek() == ' ') { s.get(); } 
    getline(s, address, ',');
    while (s.peek() == ',') { s.get(); }
    getline(s, hours, ',');
    string x,y;
    while (s.peek() == ',') { s.get(); }
    getline(s, x, ',');
    while (s.peek() == ' ') { s.get(); }
    getline(s, y);
  
    pos = Position(stof(x),stof(y));
}

void CampusLocation::Write(std::ostream& s) const {
    int x = pos.GetX();
    int y = pos.GetY();
    s << "campuslocation" << endl;
    s << name << "," << address << "," << hours << "," << x << "," << y <<endl;
}

Location* CampusLocation::Clone() { return new CampusLocation(name, address, hours); }
