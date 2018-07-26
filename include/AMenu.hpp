/*
** EPITECH PROJECT, 2018
** AMenu
** File description:
** Declaration of AMenu
*/

#ifndef NANOTEKSPICE_AMENU_HPP
	#define NANOTEKSPICE_AMENU_HPP

#include <iostream>
#include <IMenu.hpp>

namespace arc
{
	class AMenu : public IMenu
	{
	public:
		AMenu();
		virtual ~AMenu();
		const std::vector<std::string> &getLibs() const override;
		const std::vector<std::string> &getGames() const override;
		int getLibIdx() const override;
		int getGamesIdx() const override;
		void setLibs(const std::vector<std::string> &) override;
		void setGames(const std::vector<std::string> &) override;
		void setLibIdx(int) override;
		void setGamesIdx(int) override;
		State getState() const override;
		void setState(State state) override;
		const std::string &getName() const override;
		void setName(const std::string &name) override;
		void setScores(
			const std::map<std::string, std::vector<std::string>> &) override;
		const std::map<std::string, std::vector<std::string>> &
		getScores() const override;
	protected:
		std::string playerName;
		int gamesIdx;
		int libIdx;
		std::vector<std::string> games;
		std::vector<std::string> libs;
		State state;
		std::string name;
		std::map<std::string, std::vector<std::string>> scores;
	};
}

#endif //NANOTEKSPICE_AMENU_HPP
