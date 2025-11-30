#include "bplus_tree.h"
#include <vector>
using namespace std;

BPlusLeaf::BPlusLeaf() {
	numGenres = 0;
	// vector of genres (keys) is empty
	// vector of vectors of games (values) is empty - 1 vector of Games per genre
	next = nullptr; // doesn't point to anything
}

void BPlusLeaf::insert(Game game) {
	for (int i = 0; i < numGenres; i++) {
		if (genres[i] == game.genre) 
		{
			games[i].push_back(game);
			return;
		}
	}

	int index = numGenres;
	for (int j = 0; j < numGenres; j++) {
		if (game.genre < genres[j]) // will shift genres[j] to the right + insert new genre
		{
			index = j; // where to insert new genre
			break;
		}
	}

	genres.insert(genres.begin() + index, game.genre);
	games.insert(games.begin() + index, vector<Game>{game}); // adds game to corresponding vector
	numGenres++;
}

vector<Game>* BPlusLeaf::search(string genre) {
	for (int i = 0; i < numGenres; i++) {
		if (genres[i] == genre)
			return &games[i]; // returns ptr b/c need to return nullptr if DNE
	}
	return nullptr;
}

bool BPlusLeaf::isFull(int maxKeys) {
	if (numGenres >= maxKeys)
		return true;

	return false;
}

BPlusLeaf* BPlusLeaf::splitLeafHelper() {
	
	BPlusLeaf* newLeaf = new BPlusLeaf();

	int mid = numGenres / 2; // split the leaf

	for (int i = mid; i < numGenres; i++) { // copy only second half to newLeaf
		if (i >= genres.size() / 2) {
			newLeaf->genres.push_back(genres[i]);
			newLeaf->games.push_back(games[i]);
		}
	}

	genres.erase(genres.begin() + mid, genres.end()); // erase second half from old leaf
	games.erase(games.begin() + mid, games.end());

	newLeaf->numGenres = newLeaf->genres.size();
	numGenres = genres.size();

	newLeaf->next = this->next; // first - set newLeaf's next to currLeaf's next
	this->next = newLeaf; // then - set currLeaf's next to newLeaf (like a linkedlist)
	return newLeaf; // return first element of newLeaf
}