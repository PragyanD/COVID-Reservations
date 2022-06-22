
#ifndef MENUS
#define MENUS
#include "LocationList.h"
#include "User.h"

void printMainMenu();
void printTestingLocations(const LocationList& locations);
void printReservationLocations(const LocationList& locations);
void printSymptomChecker(const std::string symptoms[], const bool selected[]);
void printUserDataMenu(const User& user);
void printSettingsMenu(const bool is_metric);
#endif
