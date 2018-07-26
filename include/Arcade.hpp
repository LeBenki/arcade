/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Declaration of Arcade
*/

#ifndef NANOTEKSPICE_ARCADE_HPP
	#define NANOTEKSPICE_ARCADE_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <dirent.h>
#include <bits/unique_ptr.h>
#include "IDisplayModule.hpp"
#include "IGame.hpp"
#include "DLLoader.hpp"
#include "AMenu.hpp"
#include "ScoreManager.hpp"
#include "ArcadeExceptions.hpp"

namespace arc
{
	class Arcade
	{
	typedef void (Arcade::*eventAction)();
	public:
		explicit Arcade(const std::string &);
		virtual ~Arcade();
		void addInstance(const std::string &, bool isLib);
		void readDirectory(const std::string &);
		void gameLoop();
		void nextGame();
		void previousGame();
		void nextLib();
		void previousLib();
		void setMenuStrings();
		void useEvents(const std::vector<arc::IGame::Event> &);
		void updateLib();
		void closeLibs();
		void downMenuAction();
		void upMenuAction();
		void enterMenuAction();
		void returnMenuAction();
		void goBackToTheMenu();
		void resetGame();
		void initMapEvents();
	private:
		std::string firstLib;
		std::vector<std::unique_ptr<IDisplayModule>> libs;
		std::vector<std::unique_ptr<IGame>> games;
		unsigned int idxLib;
		unsigned int idxGames;
		std::vector<DLLoader *> loaders;
		AMenu menu;
		bool runGame;
		IDisplayModule::State displayState;
		bool found;
		ScoreManager scoreManager;
		std::map<arc::IGame::Event, eventAction> mapEvents;
	};
}

#endif //NANOTEKSPICE_ARCADE_HPP
