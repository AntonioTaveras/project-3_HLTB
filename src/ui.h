#pragma once
#include <string>
#include "game.h"
using namespace std;

class  UI{
public:
    string genre;
    int hours;
    bool perDay; // True = Day, False = Week
    bool hasDeadline;
    int goalAmount; // The number of goals
    int goalUnit; // ex. 1 days, 2 weeks, 3 months, 4 years
};