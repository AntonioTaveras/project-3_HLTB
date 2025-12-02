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
    cout << "Please enter your preferred genre: ";
    cin >> genre;

    cout << "Will you enter your available time per day or week? (d/w): ";
    char dayOrWeek;
    cin >> dayOrWeek;
    while(dayOrWeek != 'd' && dayOrWeek != 'D' && dayOrWeek != 'w' && dayOrWeek != 'W'){
        cout << "The input is invalid. Please try again" << endl;
        cout << "Will you enter your available time per day or week? (d/w): ";
        cin >> dayOrWeek;
    }
    if(dayOrWeek == 'd' || dayOrWeek == 'D'){
        isPerDay = true;
    }else{
        isPerDay = false;
    }

    if(isPerDay){
        cout << "How many hours can you play per day?: ";
        cin >> hours;
        while(hours <= 0){
            cout << "The input is invalid. Please try again" << endl;
            cout << "How many hours can you play per day?: ";
            cin >> hours;
        }
    }else{
        cout << "How many hours can you play per week?: ";
        cin >> hours;
        while(hours <= 0){
            cout << "The input is invalid. Please try again" << endl;
            cout << "How many hours can you play per week?: ";
            cin >> hours;
        }
    }

    cout<< "Would you like to complete it by a certain day? (i.e. before the new semester begins or before hiatus/leave of absence is over) (y/n): " << endl;
    char comp;
    cin >> comp;
    while(comp != 'y' && comp != 'Y' && comp != 'n' && comp != 'N'){
        cout << "The input is invalid. Please try again" << endl;
        cout<< "Would you like to complete it by a certain day? (i.e. before the new semester begins or before hiatus/leave of absence is over) (y/n): " << endl;
        cin >> comp;
    }
    if(comp == 'y' || comp == 'Y'){
        hasDeadline = true;
        cout << "Please enter your goal (ex. 1, 2, 3, 4, ...)" << endl;
        cin >> goalAmount;
        while(goalAmount <= 0){
        cout << "The inupt is invalid. Please try again" << endl;
        cout << "Please enter your goal (ex. 1, 2, 3, 4, ...)" << endl;
        cin >> goalAmount;
        }
        cout << "Enter the unit (0=days, 1=weeks, 2=months, 3=years) ";
        cin >> goalUnit;
        while(goalUnit < 0 || goalUnit > 3){
            cout << "The input is invalid. Please try again" << endl;
            cout << "Enter the unit (0=days, 1=weeks, 2=months, 3=years) ";
            cin >> goalUnit;
        }
    }else{
        hasDeadline = false;
    }
}

void UI::showRecommendations(const vector<Game>& genreGames) const{
    if(genreGames.empty()){
        cout << "There is no game for you" << endl;
        return;
    }

    auto filtered = filterGames(genreGames);
    if(filtered.empty()){
        cout << "There is no game for you" << endl;
        return;
    }

    cout << "=================" << endl;
    cout << "Recommended Games" << endl;
    cout << "=================" << endl;

    for(const Game& g : filtered){
        cout << "Title: " << g.name << " | Play Hours: " << g.main_hours << endl;
    }
}

// filter genreGames based on user input (time and deadline)
vector<Game> UI::filterGames(const vector<Game>& genreGames) const{
    vector<Game> result;

    // Calculate playable time per week
    double playableTime;
    if(isPerDay){
        playableTime = hours * 7.0;
    }else{
        playableTime = hours;
    }

    // Calculate playable period
    double weeks;
    if(!hasDeadline){
        return genreGames;
    }

    // Decide weeks based on goalAmount and goalUnit if there is a deadline
    switch(goalUnit){
        case 0:
        weeks = goalAmount / 7.0;
        break;

        case 1:
        weeks = goalAmount;
        break;
        
        case 2:
        weeks = goalAmount * 4.0;
        break;

        case 3:
        weeks = goalAmount * 52.0;
        break;

        default:
        weeks = goalAmount;
        break;
    }

    // Total playable time
    double totalPlayableTime = playableTime * weeks;

    // Keep only thosw that match the criteria from genreGames
    for(const Game& g : genreGames){
        if(g.main_hours <= totalPlayableTime){
            result.push_back(g);
        }
    }
    return result;
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