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

    // string=the name of genre, vector<Game> = list of games that belong to this genre
    unordered_map<string, vector<Game>> genreToGames;

    // Group each game under its genre
    for(const Game& g : separated){
        genreToGames[g.genre].push_back(g);
    }
    
    // Insert each genre and its game list into the hash table
    for(const auto& p : genreToGames){
        Entry e;
        e.genre = p.first; // p.first = Genre name (ex. "Action")
        e.games = p.second; // p.second = All games for this genre
        size_t bucketIndex = hash(e.genre); // change genre to bucket index
        table[bucketIndex].push_back(e);
    }
}

// Look up all games for the given genre
bool HashTable::findGames(const std::string& genre, vector<Game>& genreGames) const {
    size_t bucketIndex = hash(genre);
    const auto& chain = table[bucketIndex];

    for(const Entry& e : chain){
        if(e.genre == genre){
            genreGames = e.games;
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

