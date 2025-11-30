#include "game.h"
#include <string>
#include <vector>
using namespace std;

class BPlusLeaf {

private:
	vector<string> genres; // key
	int numGenres; // tracks amount of keys

	vector<vector<Game>> games; // values
	BPlusLeaf* next; // next ptr since all leaves are connected like a linked list

public:
	BPlusLeaf(); // constructor

	void insert(Game game);
	vector<Game>* search(string genre);
	bool isFull(int maxKeys);
	BPlusLeaf* splitLeafHelper();

	// Getters
	vector<string>& getGenres();
	int getNumGenres();
	vector<vector<Game>>& getGames();
	// Setters
};

class BPlusInternal {

private:
	vector<string> keys; 
	int numKeys;

	vector<BPlusInternal*> internalChildren;
	vector<BPlusLeaf*> leafChildren; // internal points to leaf nodes
	
public:
	BPlusInternal(); // constructor
	bool isFull(int maxKeys);

	void addInternalChild(BPlusInternal* child);
	void addLeafChild(BPlusLeaf* child);
	void insertGenre(string genre);

	BPlusInternal* splitInternalHelper();

	// Getters
	vector<string>& getKeys();
	vector<BPlusLeaf*> getLeafChildren();
	vector<BPlusInternal*> getInternalChildren();
	// Setters

};

class BPlusTree {
private:
	void* root; // https://www.geeksforgeeks.org/cpp/cpp-void-pointer/
	bool hasLeafRoot;
	int keyCapacity; // max keys in one node

public:
	BPlusTree(int maxKeys = 3); // max 3 keys in one node - can change later
	void insert(Game game);
	vector<Game>* search(string genre);

	BPlusLeaf* findGenre(string genre); // returns leaf with specified genre
};