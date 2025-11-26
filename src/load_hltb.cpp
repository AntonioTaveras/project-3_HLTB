#include "load_hltb.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> parse_csv_line(const string& line)
{
    vector<string> fields;
    string field;
    bool quotes = false;

    for (size_t i = 0; i < line.size(); i++)
    {
        char c = line[i];

        if (c == '"')
        {
            quotes = !quotes;
            continue;
        }

        if (c == ',' && !quotes)
        {
            fields.push_back(field);
            field.clear();
            continue;
        }

        // add the character to current field
        field += c;

    }
    fields.push_back(field);

    return fields;
}


vector<Game> load_data(const string& csv_path)
{
    vector<Game> games;

    ifstream file(csv_path);
    if (!file.is_open())
    {
        cerr << "File " << csv_path << " could not open" << endl;
        return games;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        vector<string> fields = parse_csv_line(line);

        cout << "Row has " << fields.size() << " fields" << endl;/// DEBUG
        break;                                                   ///


    }

    return games;
}