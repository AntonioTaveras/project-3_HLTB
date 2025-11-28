#pragma once
#include "game.h"
#include <iostream>
#include <vector>
#include <list>

class HashTable{
public:
	HashTable(size_t bucketNum = 101);
	void makeTable(const std::vector<Game>& games);
	bool getAverage(const std::string& genre, double& avgHours) const;

private:
	struct Entry{
		std::string genre;
		double totalHours;
		int gamesNum; // The number of games for the genre
	};

	std::vector<std::list<Entry>> table;
	size_t hash(const std::string& key) const;
};