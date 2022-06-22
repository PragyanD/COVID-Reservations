
#ifndef USER_CLASS
#define USER_CLASS

#include <string>
#include <vector>
#include "LocationList.h"
#include "Position.h"

// Going with class approach here, with lots of getters and setters.
// Another option would be to have fewer getters/setters, and make a "settings" class as "friend."
class User {
private:
    std::string f_name, l_name;
    int age;
    float height, weight;
    LocationList reservations;
    std::vector<Position> positions;
    bool is_metric;
    std::string user_filename, reservations_filename, positions_filename;

    // private helper function for reading the positions.
    void _ReadPositions(const std::string fname);
public:
    // Param'd constructor with defaults.
    // Using initialization list to ensure there's no weird stuff happening with allocation.
    User(std::string init_fname="John", std::string init_lname="Doe", int init_age=0,    float init_height=0.0, float  init_weight=0.0) :
              f_name(init_fname),            l_name(init_lname),      age(init_age),    height(init_height),    weight(init_weight),
              reservations(),                positions(),             is_metric(false), user_filename("default.txt"),
              reservations_filename("default_reservations.txt"),      positions_filename("default_positions.txt")     {}

    // One-liners, implementing inline in header:
    std::string to_string() const { return f_name + " " + l_name; }

    std::string GetFirst() const { return f_name; }
    void SetFirst(const std::string new_first) { f_name = new_first; }

    std::string GetLast() const {return l_name; }
    void SetLast(const std::string new_last);

    int GetAge() const {return age; }
    void SetAge(const int new_age) { age = new_age; }

    float GetHeight() const {return height; }
    void SetHeight(const float new_height) { height = new_height; }

    float GetWeight() const {return weight; }
    void SetWeight(const float new_weight) { weight = new_weight; }

    bool IsMetric() const { return is_metric; }
    void SetUnits(const bool set_metric);

    // Longer functions implementing in .cpp:
    void MakeReservation(Location* reserve);

    int CheckExposures() const;

    void PrintData() const;

    void PrintReservations() const;

    void Read(bool& is_imperial, std::string fname="");

    void Write(const bool is_imperial);

    Position AveragePosition() const;
  
    
};
#endif
