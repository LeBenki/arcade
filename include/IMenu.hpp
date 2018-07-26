/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Declaration of Arcade
*/

#ifndef NANOTEKSPICE_IMENU_HPP
	#define NANOTEKSPICE_IMENU_HPP

#include <vector>
#include <string>
#include <map>

#define GAMETITLE "Vapeur"

namespace arc
{
	class IMenu
	{
	public:
		enum State
		{
			GAME,
			LIBRARY,
			PLAYER
		};
		virtual ~IMenu() = default;
		virtual const std::vector<std::string> &getLibs() const = 0;
		virtual const std::vector<std::string> &getGames() const = 0;
		virtual int getLibIdx() const = 0;
		virtual int getGamesIdx() const = 0;
		virtual void setLibs(const std::vector<std::string> &) = 0;
		virtual void setGames(const std::vector<std::string> &) = 0;
		virtual void setLibIdx(int) = 0;
		virtual void setGamesIdx(int) = 0;
		virtual State getState() const = 0;
		virtual void setState(State state) = 0;
		virtual const std::string &getName() const = 0;
		virtual void setName(const std::string &name) = 0;
		virtual void setScores(
			const std::map<std::string, std::vector<std::string>> &) = 0;
		virtual const std::map<std::string, std::vector<std::string>> &
		getScores() const = 0;
	};
}

#endif //NANOTEKSPICE_IMENU_HPP
