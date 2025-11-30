#pragma once
#include "game.h"
#include <vector>
#include <list>
#include <string>

class HashTable{
public:
	HashTable(size_t bucketNum = 101);
	void makeTable(const std::vector<Game>& games);
	bool findAverage(const std::string& genre, double& avgHours) const;

private:
	struct Entry{
		std::string genre;
		double avgHours;
	};

	std::vector<std::list<Entry>> table;
	size_t hash(const std::string& key) const;
};