#include "load_hltb.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	vector<Game> games = load_data("data/hltb_dataset.csv");
	return 0;
}