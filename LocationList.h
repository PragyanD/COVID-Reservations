//Name: Pragyan Das
//WISCID: pdas7
#ifndef LOCATION_LIST
#define LOCATION_LIST

#include <string>
#include <vector>
#include "Location.h"

class LocationList {
private:
    std::vector<Location*> list;
public:
    LocationList();
    ~LocationList();
    int GetCount() const { return list.size(); }
    Location* GetLocation(int i) const { return list[i]; }
    void AddLocation(Location* new_loc);
    void FromFile(std::string fname);
    void ToFile(std::string fname);
    void Sort(Position p);
    class Closer{
        private:
        Position pos;
        public:
        Closer(Position p) : pos(p){}
        bool operator()(Location* a, Location* b){
            if((*a-pos)<(*b-pos)){
                return true;
            }
            return false;
        }
    
    };
};

#endif
