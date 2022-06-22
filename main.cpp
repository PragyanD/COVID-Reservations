#include <iostream>
#include <string>
#include "menus.h"

using namespace std;

const int NUM_SYMPTOMS = 6;

const string symptoms[NUM_SYMPTOMS] = {"Fever", "Cough", "Shortness of breath", "Loss of taste or smell", "Fatigue", "Sore throat"};

enum MAIN_MENU {VIEW_LOCS=1, MAKE_RESERVE=2, SYMPTOMS=3, EXPOSURES=4, VIEW_RESERVE=5, VIEW_DATA=6, SET_DATA=7, SETTINGS=8, MAIN_EXIT=9};
enum SYMPT_MENU {SUBMIT=NUM_SYMPTOMS+1, CANCEL=NUM_SYMPTOMS+2};
enum DATA_MENU {FIRST_NAME=1, LAST_NAME=2, AGE=3, HEIGHT=4, WEIGHT=5, DATA_EXIT=6};
enum SETT_MENU {UNIT=1, LOAD=2, SAVE=3, SETT_EXIT=4};

// Helper functions to handle the submenus.
void SymptomCheckerMenu();
void SetDataMenu(User& user);
void SettingsMenu(User& user);
string ReadFName();
string ReadLName();
int ReadAge(float MAX);
float ReadHeight(float MAX, string UNIT);
float ReadWeight(float MAX, string UNIT);

// Other helper functions
int getMenuInput() {
    int input;
    cin >> input;
    while (!cin) {
        cin.clear();
        cin.ignore(500, '\n');
        cout << "Please input a valid menu item: ";
        cin >> input;
    }
    cin.get(); // read and ignore the whitespace character after input (so a \n isn't left behind).
    return input;
}

void PressEnterToReturn() {
    char g_input = cin.get();
    if (g_input != '\n') { cin.ignore(500, '\n'); }
}

int main() {
    User user = User();
    LocationList locations = LocationList();
    bool dummy = user.IsMetric();
    user.Read(dummy); // passing a dummy, User will store own is_metric anyway.
    locations.FromFile("locations.txt");
    int NUM_LOCATIONS = locations.GetCount();
    int input;
    do {
        printMainMenu();
        input = getMenuInput();
        switch (input) {
            case VIEW_LOCS: {
                int t_input;
                do {
                    locations.Sort(user.AveragePosition());
                    printTestingLocations(locations);
                    t_input = getMenuInput();
                    if (t_input >= 1 && t_input <= NUM_LOCATIONS) {
                        locations.GetLocation(t_input-1)->Print();
                        cout << "Press enter to return to locations menu." << endl;
                        PressEnterToReturn();
                    }
                    else if (t_input == NUM_LOCATIONS+1) {
                        break;
                    }
                    else {
                        cout << "Invalid menu item!" << endl;
                    }
                } while (t_input != NUM_LOCATIONS+1);
                break;
            }
            case MAKE_RESERVE: {
                int r_input = 0;
                do {
                    locations.Sort(user.AveragePosition());
                    printReservationLocations(locations);
                    r_input = getMenuInput();
                    if (r_input >= 0 && r_input < NUM_LOCATIONS) {
                        Location* to_reserve = locations.GetLocation(r_input);
                        if (to_reserve->IsReservable())
                            user.MakeReservation(to_reserve);
                        else
                            cout << "Invalid entry, please enter a valid reservation location!" << endl;
                    }
                    else if (r_input == NUM_LOCATIONS) {
                        break;
                    }
                    else {
                        cout << "Invalid menu item!" << endl;
                    }
                } while (r_input != NUM_LOCATIONS);
                break;
            }
            case SYMPTOMS:
                SymptomCheckerMenu();
                break;
            case EXPOSURES: {
                int exposures = user.CheckExposures();
                if (exposures == 0) {
                    cout << "No Covid-19 exposures detected!" << endl;
                }
                else {
                    cout << "Found " << exposures << " possible Covid-19 exposures, please arrange to be tested for Covid-19." << endl;
                }
                cout << "Press enter to return to main menu." << endl;
                PressEnterToReturn();
                break;
            }
            case VIEW_RESERVE:
                user.PrintReservations();
                PressEnterToReturn();
                break;
            case VIEW_DATA:
                user.PrintData();
                PressEnterToReturn();
                break;
            case SET_DATA: {
                SetDataMenu(user);
                break;
            }
            case SETTINGS: {
                SettingsMenu(user);
                break;
            }
            case MAIN_EXIT:
                break;
            default:
                cout << "Invalid menu item!" << endl;
                break;
        }
    } while (input != MAIN_EXIT);

    return 0;
}

void SymptomCheckerMenu() {
    bool selected[NUM_SYMPTOMS] = {false, false, false, false, false, false};
    int s_input;
    do {
        printSymptomChecker(symptoms, selected);
        s_input = getMenuInput();
        if (s_input >= 1 && s_input <= NUM_SYMPTOMS) {
            selected[s_input-1] = !selected[s_input-1];
        }
        else if (s_input == SUBMIT) {
            int num_selected = 0;
            for (int i = 0; i < NUM_SYMPTOMS; i++) {
                if (selected[i]) {
                    num_selected++;
                }
            }
            if (num_selected > 2) {
                cout << "Please go to an available testing site to be tested for Covid-19." << endl
                     << "Press enter to return to main menu." << endl;
            }
            else if (num_selected > 0 && num_selected <= 2) {
                cout << "Please stay home and monitor your symptoms. If you symptoms persist or you develop new symptoms, please go to an available testing site to be tested for Covid-19." << endl
                     << "Press enter to return to main menu." << endl;
            }
            else {
                cout << "You seem to be feeling fine. Remember to test regularly for Covid-19." << endl
                     << "Press enter to return to main menu." << endl;
            }
            for (int i = 0; i < NUM_SYMPTOMS; i++) {
                selected[i] = false;
            }
            PressEnterToReturn();
        }
        else if (s_input == CANCEL) {
            break;
        }
        else {
            cout << "Invalid menu item!" << endl;
        }
    } while (s_input != SUBMIT && s_input != CANCEL);
}

void SetDataMenu(User& user) {
    int data_input = 0;
    do {
       printUserDataMenu(user);
       cin >> data_input;
       switch (data_input) {
           case FIRST_NAME: {
              string fname = ReadFName();
              user.SetFirst(fname);
              break;
           }
           case LAST_NAME: {
              string lname = ReadLName();
              user.SetLast(lname);
              break;
           }
           case AGE: {
              int MAX_AGE = 122;
              int age = ReadAge(MAX_AGE);
              user.SetAge(age);
              break;
           }
           case HEIGHT: {
              float  HT_MAX  = user.IsMetric() ? 2.75 : 9;
              string HT_UNIT = user.IsMetric() ? "m"  : "ft";
              float height = ReadHeight(HT_MAX, HT_UNIT);
              user.SetHeight(height);
              break;
           }
           case WEIGHT: {
              float  WT_MAX  = user.IsMetric() ? 445  : 975;
              string WT_UNIT = user.IsMetric() ? "kg" : "lbs";
              float weight = ReadWeight(WT_MAX, WT_UNIT);
              user.SetWeight(weight);
              break;
           }
           case DATA_EXIT:
              break;
           default:
              cout << "Invalid menu item!" << endl;
       }
    } while (data_input != DATA_EXIT);
}

void SettingsMenu(User& user) {
    int s_input = 0;
    do {
       printSettingsMenu(user.IsMetric());
       s_input = getMenuInput();
       switch (s_input) {
           case UNIT:
           {
               bool is_metric = user.IsMetric(); // use temp local variable, so we don't need to keep calling function.
               is_metric = !is_metric;
               user.SetUnits(is_metric);
               string new_unit = is_metric ? "metric" : "imperial";
               string previous_unit = is_metric ? "imperial" : "metric";
               cout << "Switching from " << previous_unit << " to " << new_unit << " units." << endl;
               break;
           }
           case LOAD:
           {
               string username;
               cout << "Please enter your last name: ";
               cin >> username;
               bool dummy = user.IsMetric(); // use dummy, later we'll have access to whatever User read and stored.
               user.Read(dummy, username + ".txt");
           }
           case SAVE:
           {
               user.Write(!user.IsMetric());
               cout << "Saved " << user.GetLast() << ".txt." << endl;
           }
           case SETT_EXIT:
              break;
           default:
              cout << "Invalid menu item!" << endl;
       }
    } while (s_input != SETT_EXIT);
}

string ReadFName() {
    string fname;
    cout << "Please enter your first name: ";
    cin >> fname;
    return fname;
}

string ReadLName() {
    string lname;
    cout << "Please enter your last name: ";
    cin >> lname;
    return lname;
}

int ReadAge(float MAX) {
    int age;
    cout << "Please enter your age: ";
    cin >> age;
    while (!cin || age < 0 || age > MAX) {
        if (!cin) {
            cin.clear();
            cin.ignore(500, '\n');
            cout << "Invalid input, please enter a valid age: ";
        }
        else {
            cout << "Invalid age of " << age << ", please enter a valid age: ";
        }
        cin >> age;
    }
    return age;
}

float ReadHeight(float MAX, string UNIT) {
    float height;
    cout << "Please enter your height: ";
    cin >> height;
    while (!cin || height < 0 || height > MAX) {
        if (!cin) {
            cin.clear();
            cin.ignore(500, '\n');
            cout << "Invalid input, please enter a valid height: ";
        }
        else {
            cout << "Invalid height of " << height << " " << UNIT << ", please enter a valid height: ";
        }
        cin >> height;
    }
    return height;
}

float ReadWeight(float MAX, string UNIT) {
    float weight;
    cout << "Please enter your weight: ";
    cin >> weight;
    while (!cin || weight < 0 || weight > MAX) {
        if (!cin) {
            cin.clear();
            cin.ignore(500, '\n');
            cout << "Invalid input, please enter a valid weight: ";
        }
        else {
            cout << "Invalid weight of " << weight << " " << UNIT << ", please enter a valid weight: ";
        }
        cin >> weight;
    }
    return weight;
}
