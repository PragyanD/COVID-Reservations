#ifndef CAMPUS_LOCATION
#define CAMPUS_LOCATION

#include <iostream>
#include <string>
#include "Location.h"

class CampusLocation : public Location {
public:

    CampusLocation(std::string init_name = "Campus Location",  std::string init_addr  = "500 Lincoln Drive",
                   std::string init_hours = "9:00am-5:00pm") : Location(init_name, init_addr, init_hours, 0) {}

    bool Reserve() override;


    void Cancel() { }

    void Print() const override;

    void Read(std::istream& s) override;

    void Write(std::ostream& s) const override;

    Location* Clone() override;
};
#endif
