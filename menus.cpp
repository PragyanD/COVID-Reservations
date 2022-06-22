
#include <iostream>
#include <iomanip>
#include <string>
#include "menus.h"
#include "LocationList.h"
#include "Location.h"

using namespace std;

void printMainMenu() {
    cout << "Welcome (back) to Safe-ish Badgers!" << endl
         << "[1] View testing locations" << endl
         << "[2] Make test reservation" << endl
         << "[3] Use symptom checker" << endl
         << "[4] Check for Covid-19 Exposures" << endl
         << "[5] View my reservations" << endl
         << "[6] View my personal data" << endl
         << "[7] Adjust my personal data" << endl
         << "[8] Change settings" << endl
         << "[9] Exit program" << endl
         << "Please enter a menu item: ";
}

void printTestingLocations(const LocationList& locations) {
    cout << "Testing Locations:" << endl;
    for (int i=0; i < locations.GetCount(); i++) {
        cout << "[" << i+1 << "] " << locations.GetLocation(i)->to_string() << endl;
    }
    cout << "[" << locations.GetCount()+1 << "] Return to main menu" << endl
         << "Choose a location for more information, or return to the menu: ";
}

void printReservationLocations(const LocationList& locations) {
    int count = locations.GetCount();
    for (int i = 0; i < count; i++) {
        Location* next = locations.GetLocation(i);
        if (next->IsReservable())
            cout << "[" << i << "] " << next->to_string() << endl;
    }
    cout << "[" << count << "] Return to main menu" << endl
         << "Choose a location to reserve, or return to the menu: ";
}

void printSymptomChecker(const string symptoms[], const bool selected[]) {
    cout << "Select Your Symptoms:" << left << endl;
    for (int i = 0; i < 6; i++) {
        string next = "[" + to_string(i+1) + (selected[i] ? "*" : "") + "]";
        cout << setw(5) << next << symptoms[i] << endl;
    }
    cout << "[7]  Submit Symptoms" << endl
         << "[8]  Cancel and return to main menu" << endl;
}

void printUserDataMenu(const User& user) {
    cout << "Set your personal data:" << endl
         << "[1] First name (" << user.GetFirst() << ")" << endl
         << "[2] Last name (" << user.GetLast() << ")" << endl
         << "[3] Age (" << user.GetAge() << ")" << endl
         << "[4] Height (" << user.GetHeight() << " " << (user.IsMetric() ? "m"  : "ft" ) << ")" << endl
         << "[5] Weight (" << user.GetWeight() << " " << (user.IsMetric() ? "kg" : "lbs") << ")" << endl
         << "[6] Return to main menu" << endl
         << "Please enter a menu item:";
}

void printSettingsMenu(const bool is_metric) {
   cout << "Change your app settings:" << endl
        << "[1] Switch units (" << (is_metric ? "metric" : "imperial") << ")" << endl
        << "[2] Load Data" << endl
        << "[3] Save Data" << endl
        << "[4] Return to main menu" << endl
        << "Please enter a menu item: ";
}
