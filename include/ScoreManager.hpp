/*
** EPITECH PROJECT, 2018
** ScoreManager
** File description:
** Declaration of ScoreManager
*/

#ifndef NANOTEKSPICE_SCOREMANAGER_HPP
	#define NANOTEKSPICE_SCOREMANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>

namespace arc
{
	class ScoreManager
	{
	public:
		explicit ScoreManager(const std::string & = ".score");
		virtual ~ScoreManager();
		void addScore(const std::string &game, const std::string &name,
			      long score);
		long getBestScoreFromName(const std::string &game,
					  const std::string &name);
		long getBestScoreFromGame(const std::string &game);
		const std::vector<std::string>
		getScoresForGame(const std::string &game);
		const std::map<std::string, std::vector<std::string>>
		getTopScore(const std::vector<std::string> &games);
	private:
		std::ofstream myfile;
		std::vector<std::string> scores;
	};
}

#endif //NANOTEKSPICE_SCOREMANAGER_HPP
