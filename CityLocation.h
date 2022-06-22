#ifndef CITY_LOCATION
#define CITY_LOCATION

#include <iostream>
#include <string>
#include "Location.h"

class CityLocation : public Location {
public:
    CityLocation(std::string init_name = "City Location",  std::string init_addr  = "2 E Main Street",
                 std::string init_hours = "9:00am-5:00pm", int init_reserves = 0) :
        Location(init_name, init_addr, init_hours, init_reserves) {}

    bool Reserve() override;

    void Cancel() { reservations++; }

    void Print() const override;

    void Read(std::istream& s) override;

    void Write(std::ostream& s) const override;

    Location* Clone() override;
};
#endif
