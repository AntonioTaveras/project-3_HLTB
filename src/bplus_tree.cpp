#include "bplus_tree.h"
#include <vector>
using namespace std;

/* ====== LEAF Functions ====== */
BPlusLeaf::BPlusLeaf() {
	numGenres = 0;
	// vector of genres (keys) is empty
	// vector of vectors of games (values) is empty - 1 vector of Games per genre
	next = nullptr; // doesn't point to anything
}

void BPlusLeaf::insert(Game game) {
	for (int i = 0; i < numGenres; i++) {
		if (genres[i] == game.genre) // if genre already exists in leaf,
		{
			games[i].push_back(game); // push game in the genre's game vector
			return;
		}
	}

	// if genre DNE,
	int index = numGenres;
	for (int j = 0; j < numGenres; j++) {
		if (game.genre < genres[j]) // find where to input genre on the leaf
		{
			index = j; // index where to insert new genre
			break;
		}
	}

	genres.insert(genres.begin() + index, game.genre); // adds genre to leaf
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

	// copy only second half to newLeaf
	for (int i = mid; i < numGenres; i++) { 
		if (i >= genres.size() / 2) {
			newLeaf->genres.push_back(genres[i]);
			newLeaf->games.push_back(games[i]);
		}
	}

	// erase second half from old leaf
	genres.erase(genres.begin() + mid, genres.end()); 
	games.erase(games.begin() + mid, games.end());

	newLeaf->numGenres = newLeaf->genres.size();
	numGenres = genres.size();

	newLeaf->next = this->next; // first - set newLeaf's next to currLeaf's next
	this->next = newLeaf; // then - set currLeaf's next to newLeaf (like a linkedlist)
	return newLeaf; // return first element of newLeaf
}

vector<string>& BPlusLeaf::getGenres() {
	return genres;
}

vector<vector<Game>>& BPlusLeaf::getGames() {
	return games;
}

int BPlusLeaf::getNumGenres() {
	return numGenres;
}

/* ====== INTERNAL NODE Functions ====== */
vector<BPlusLeaf*> BPlusInternal::getLeafChildren() {
	return leafChildren;
}

BPlusInternal::BPlusInternal() {

}

bool BPlusInternal::isFull(int maxKeys) {

}

void BPlusInternal::addInternalChild(BPlusInternal* child) {

}

void BPlusInternal::addLeafChild(BPlusLeaf* child) {
	if (leafChildren.empty()) {
		leafChildren.push_back(child);
		return;
	}

	// if there are already leaf children, then need to insert in correct order
	int index = leafChildren.size(); // to add it to the end

	for (int i = 0; i < keys.size(); i++) { // check sorted (alphabetical?) order
		if (child->getGenres()[0] < keys[i]) {
			index = i;
			break;
		}
	}

	leafChildren.insert(leafChildren.begin() + index, child);
}

void BPlusInternal::insertGenre(string genre) {
	if (numKeys == 0) {
		keys.push_back(genre);
		numKeys++;
		return;
	}

	// basically like BPlusLeaf insert()
	int index = numKeys;
	for (int j = 0; j < numKeys; j++) {
		if (genre < keys[j]) // will shift genres[j] to the right + insert new genre
		{
			index = j; // where to insert new genre
			break;
		}
	}
	keys.insert(keys.begin() + index, genre);
	numKeys++;
}

BPlusInternal* BPlusInternal::splitInternalHelper() {

	// pretty much the same as splitLeafHelper()
	BPlusInternal* newInternal = new BPlusInternal();

	int mid = numKeys / 2; // split the internal node

	// copy only second half to newInternal NOT including keyUp
	for (int i = mid + 1; i < keys.size(); i++) { // mid+1 b/c doesn't include keyUp
		if (i >= keys.size() / 2) {
			newInternal->keys.push_back(keys[i]);
			newInternal->numKeys++;
		}
	}

	// copy only second half of children to newInternal
	for (int i = mid + 1; i < leafChildren.size(); i++) // mid+1 b/c child greater than it
		newInternal->leafChildren.push_back(leafChildren[i]);

	keys.erase(keys.begin() + mid, keys.end()); // erase second half from old leaf
	leafChildren.erase(leafChildren.begin() + mid + 1, leafChildren.end());

	numKeys = keys.size();

	return newInternal;
}

vector<string>& BPlusInternal::getKeys() {
	return keys;
}

vector<BPlusLeaf*> BPlusInternal::getLeafChildren() {
	return leafChildren;
}

/* ====== B+ TREE Functions ====== */
BPlusTree::BPlusTree(int maxKeys) {
	root = new BPlusLeaf(); // empty leaf
	hasLeafRoot = true; // works with void* root
	keyCapacity = maxKeys;
}

void BPlusTree::insert(Game game) {
	if (hasLeafRoot) {
		BPlusLeaf* leaf = (BPlusLeaf*) root;
		leaf->insert(game);

		if (!leaf->isFull(keyCapacity))
			return;

		// if leaf is full, split leaf and move key UP
		BPlusLeaf* rightLeaf = leaf->splitLeafHelper();

		// key moved up creates an internal node root
		BPlusInternal* internalRoot = new BPlusInternal();

		string keyUp = rightLeaf->getGenres()[0];
		internalRoot->insertGenre(keyUp);

		internalRoot->addLeafChild(leaf);
		internalRoot->addLeafChild(rightLeaf);

		root = internalRoot;
		hasLeafRoot = false;
		return;
	}

	// else - has internal root...


}

vector<Game>* BPlusTree::search(string genre) {
	if (hasLeafRoot) {
		BPlusLeaf* leaf = (BPlusLeaf*) root;
		return leaf->search(genre);
	}
	else {
		BPlusInternal* internal = (BPlusInternal*) root;

		BPlusLeaf* leaf = internal->getLeafChildren()[0]; // given only 2 levels of B+ tree - FIX: for multiple levels
		return leaf->search(genre);
	}
}

BPlusLeaf* BPlusTree::findGenre(string genre) {
	if (hasLeafRoot)
		return (BPlusLeaf*) root;

	BPlusInternal* internalRoot = (BPlusInternal*) root;
	
	// 2 keys max in the root w/ 3 children total
	// this for loop gets either the left child or the child in the middle
	for (int i = 0; i < internalRoot->getKeys().size(); i++) {
		if (genre < internalRoot->getKeys()[i]) {
			return internalRoot->getLeafChildren()[i];
		}
	}

	// if key is greater than all keys, then genre is in the rightmost child
	return internalRoot->getLeafChildren()[internalRoot->getLeafChildren().size() - 1]; // get last element/child
}