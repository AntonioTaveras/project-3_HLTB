#include "load_hltb.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Game> load_data(const std::string& csv_path)
{
    std::vector<Game> games;

    std::ifstream file(csv_path);
    if (!file.is_open())
    {
        std::cerr << "File " << csv_path << " could not open" << std::endl;
        return games;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        // TODO parse lines
    }

    return games;
}