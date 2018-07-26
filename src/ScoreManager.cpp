/*
** EPITECH PROJECT, 2018
** arc::ScoreManager
** File description:
** Implementation of arc::ScoreManager
*/

#include "ScoreManager.hpp"

arc::ScoreManager::ScoreManager(const std::string &filename)
{
	std::ifstream infile(filename.c_str());
	std::string line;

	while (std::getline(infile, line))
	{
		scores.push_back(line);
	}
	myfile.open(filename.c_str(), std::fstream::in
				| std::fstream::out | std::fstream::app);
}

arc::ScoreManager::~ScoreManager()
{
	myfile.close();
}

void arc::ScoreManager::addScore(const std::string &game, const std::string &name,
			long score)
{
	std::ostringstream line;
	line << game << ":" << name << ":" << score;

	scores.push_back(line.str());
	myfile << line.str() << std::endl;
}

long arc::ScoreManager::getBestScoreFromName(const std::string &game,
					const std::string &name)
{
	std::string tmpGame;
	std::string tmpName;
	std::string tmpScore;
	long save = 0;

	for (const std::string &string : scores)
	{
		std::stringstream stream(string);
		std::getline(stream, tmpGame, ':');
		std::getline(stream, tmpName, ':');
		std::getline(stream, tmpScore, '\n');
		if (game == tmpGame && name == tmpName
			&& save < atoi(tmpScore.c_str()))
			save = atoi(tmpScore.c_str());
	}
	return save;
}

long arc::ScoreManager::getBestScoreFromGame(const std::string &game)
{
	std::string tmpGame;
	std::string tmpName;
	std::string tmpScore;
	long save = 0;

	for (const std::string &string : scores)
	{
		std::stringstream stream(string);
		std::getline(stream, tmpGame, ':');
		std::getline(stream, tmpName, ':');
		std::getline(stream, tmpScore, '\n');
		if (game == tmpGame
			&& save < atoi(tmpScore.c_str()))
			save = atoi(tmpScore.c_str());
	}
	return save;
}

static long getScoreFromLine(const std::string &line)
{
	std::stringstream stream(line);
	std::string game;
	std::string name;
	std::string scoreString;
	long score;

	getline(stream, game, ':');
	getline(stream, name, ':');
	getline(stream, scoreString, '\n');
	score = atol(scoreString.c_str());
	return score;
}

const std::map<std::string, std::vector<std::string>>
arc::ScoreManager::getTopScore(const std::vector<std::string> &games)
{
	std::map<std::string, std::vector<std::string>> map;

	for (const auto &i : games)
		map[i] = getScoresForGame(i);
	return map;
}

const std::vector<std::string>
arc::ScoreManager::getScoresForGame(const std::string &game)
{
	std::vector<std::string> gamesScore;

	for (const auto &i: scores)
		if (!i.compare(0, game.size(), game))
		{
			gamesScore.push_back(i);
		}
	std::sort(gamesScore.begin(), gamesScore.end(), [](
		const std::string &lh, const std::string &rh) {
		return getScoreFromLine(lh) > getScoreFromLine(rh);
	});
	if (gamesScore.size() > 5)
		gamesScore.resize(5);
	for (auto &i : gamesScore)
		i.replace(0, game.size() + 1, "");
	return gamesScore;
}
