#pragma once
#include <string>
#include <vector>
#include "game.h"


class  UI{

public:
    UI(); // Constructor
    void promptUser();
    std::string getGenre() const;
    int getHours() const;
    bool getIsPerDay() const;
    bool getHasDeadline() const;
    int getGoalAmount() const;
    int getGoalUnit() const;
    void showRecommendations(const std::vector<Game>& games) const;

private:
    std::string genre;
    int hours;
    bool isPerDay; // True = Day, False = Week
    bool hasDeadline;
    int goalAmount; // The number of goals
    int goalUnit; // ex. 0=days, 1=weeks, 2=months, 3=years

    std
};