#include "game.h"
#include <string>
#include <vector>
using namespace std;

class BPlusLeaf {

private:
	vector<string> genres;
	int numGenres; // tracks amount of keys

	vector<vector<Game>> games;
	BPlusLeaf* next;

public:
	BPlusLeaf(); // constructor

	void insert(string genre, vector<Game> games);
	vector<Game>* search(string genre);
	bool isFull(int maxKeys);
	BPlusLeaf* splitLeaf();

	// Getters
	// Setters
};

class BPlusInternal {

private:
	vector<string> keys; 
	int numKeys;

	vector<BPlusLeaf*> children; // internal points to leaf nodes
	
public:
	BPlusInternal(); // constructor
	bool isFull(int maxKeys);

	BPlusInternal* splitInternal();

	// Getters
	// Setters

};

class BPlusTree {
private:
	BPlusLeaf* root;
	int keyCapacity; // max keys in one node

public:
	BPlusTree(int maxKeys = 4); // l = 4 ?
	void insert(string genre, vector<Game> games);
	vector<Game>* search(string genre);

	BPlusLeaf* findGenre(string genre); // returns leaf with specified genre

	void splitLeaf(BPlusLeaf* leafChild, BPlusInternal* parent);
	void splitInternal(BPlusInternal* internalChild, BPlusInternal* parent);
};