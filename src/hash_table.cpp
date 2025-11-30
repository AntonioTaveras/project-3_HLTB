#include "hash_table.h"
#include "preprocess_data.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

HashTable::HashTable(size_t bucketNum){
    table.resize(bucketNum);
}

void HashTable::makeTable(const std::vector<Game>& games){
    vector<Game> cleaned = clean_data(games);
    vector<Game> separated = separate_genres(cleaned);
    unordered_map<string, pair<double, int>> genreStats; // pair<double, int> = pair<first, second>

    // 1. Calculate the sum of play hours by genre and the number of games by genre
    for(const Game& g : separated){
        genreStats[g.genre].first += g.main_hours; // The sum of play hours
        genreStats[g.genre].second += 1; // The number of games by genre
    }
    
    // 2. Calculate average and push them into HashTable
    for(const auto& p : genreStats){
        double sum = p.second.first; // unordered_map<first , second(pair<first, second>)>
        int count = p.second.second;
        double avg = sum / count;

        Entry e;
        e.genre = p.first;
        e.avgHours = avg;

        size_t bucketIndex = hash(e.genre);
        table[bucketIndex].push_back(e);
    }
}

bool HashTable::findAverage(const std::string& genre, double& avgHours) const {
    size_t bucketIndex = hash(genre);
    auto& chain = table[bucketIndex];
    for(const Entry& e : chain){
        if(e.genre == genre){
            avgHours = e.avgHours;
            return true;
        }
    }
    return false;
}

size_t HashTable::hash(const string& key) const{
    std::hash<string> hasher;
    size_t value = hasher(key);
    return value % table.size();
}

