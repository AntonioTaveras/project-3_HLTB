#include "preprocess_data.h"
#include "game.h"
#include <sstream>

vector<Game> clean_data(const vector<Game>& games)
{
	vector<Game> cleaned_games;

	for (const Game& game : games) // remove games without a genre or main_hours
	{
		if (!game.genre.empty() && game.main_hours > 0)
			cleaned_games.push_back(game);
	}

	return cleaned_games;
}

vector<Game> separate_genres(const vector<Game>& games)
{
	vector<Game> genre_separated_games;

	for (const Game& game : games)
	{
		stringstream stream(game.genre);
		string one_genre;

		while (getline(stream, one_genre, ','))
		{

			if (one_genre[0] == ' ') // remove space after comma
				one_genre = one_genre.substr(1);

			Game one_game = game;
			one_game.genre = one_genre;
			genre_separated_games.push_back(one_game);
		}
	}
	return genre_separated_games;
}