#include "ui.h"
#include <iostream>
using namespace std;

UI::UI()
: genre(""),
hours(0),
isPerDay(true),
hasDeadline(false),
goalAmount(0),
goalUnit(0)
{}

void UI::promptUser(){
    cout << "Backlog Breaker" << endl << endl;
    cout << "Genre ";
    cin >> genre;

    cout << "Do you want to enter your available time per day or week? (d/w) ";
    char dayOrWeek;
    cin >> dayOrWeek;
    if(dayOrWeek == 'd' || dayOrWeek == 'D'){
        isPerDay = true;
    }else{
        isPerDay = false;
    }

    cout << "How many hours can you play? ";
    cin >> hours;

    cout<< "Would you like to complete it by a certain day? (y/n)" << endl;
    char comp;
    cin >> comp;
    if(comp == 'y' || comp == 'Y'){
        hasDeadline = true;

        cout << "Please enter your goal" << endl;
        cin >> goalAmount;
        cout << "Enter the unit (0=days, 1=weeks, 2=months, 3=years) ";
        cin >> goalUnit;
    }else{
        hasDeadline = false;
    }
}

void UI::showRecommendations(const vector<Game>& games) const{
    if(games.empty()){
        cout << "There is no game for you" << endl;
        return;
    }
}

string UI::getGenre() const{
    return genre;
}

bool UI::getIsPerDay() const {
    return isPerDay;
}

int UI::getHours() const {
    return hours;
}

bool UI::getHasDeadline() const{
    return hasDeadline;
}

int UI::getGoalAmount() const{
    return goalAmount;
}

int UI::getGoalUnit() const{
    return goalUnit;
}