#include "load_hltb.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{

	vector<Game> games = load_data("data/hltb_dataset.csv");
	cout << "HLTB" << endl;

	return 0;

}