#pragma once
#include <vector>
#include "game.h"
using namespace std;

vector<Game> clean_data(const vector<Game>& games);
vector<Game> separate_genres(const vector<Game>& games);