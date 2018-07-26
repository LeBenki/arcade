/*
** EPITECH PROJECT, 2018
** arc::Arcade
** File description:
** Implementation of arc::Arcade
*/

#include "Arcade.hpp"

arc::Arcade::Arcade(const std::string &firstLib) : firstLib(firstLib),
					idxLib(0), idxGames(0), runGame(true),
					displayState(IDisplayModule::MENU),
					found(false)
{
	try
	{
		readDirectory("lib/");
		readDirectory("games/");
	}
	catch (const std::logic_error &e)
	{
		std::cerr << e.what() << std::endl;
		exit(84);
	}
	catch (const arc::LibraryUnknown &e)
	{
		std::cerr << e.what() << std::endl;
		exit(84);
	}
	setMenuStrings();
	initMapEvents();
}

arc::Arcade::~Arcade()
{

}

void arc::Arcade::addInstance(const std::string &libName, bool isLib)
{
	static unsigned int counter = 0;
	auto *loader = new DLLoader(libName);

	if (isLib)
	{
		if (libName == firstLib)
		{
			idxLib = counter;
			found = true;
		}
		libs.push_back(std::move(loader->getSymbol<IDisplayModule>(
			std::string("getInstance"))));
		++counter;
	}
	else
	{
		games.push_back(std::move(loader->getSymbol<IGame>(
			std::string("getInstance"))));
	}
	loaders.push_back(loader);
}

void arc::Arcade::readDirectory(const std::string &directory)
{
	DIR *dir = opendir(directory.c_str());
	struct dirent *dirp;
	bool isDirectory = directory == "lib/";
	std::string dirName;

	while ((dirp = readdir(dir)))
	{
		dirName = std::string(dirp->d_name);
		if (dirName[dirName.size() - 1] == 'o')
		{
			addInstance(directory + dirName, isDirectory);
		}
	}
	closedir(dir);
	if (!found)
		throw arc::LibraryUnknown(firstLib);
}

void arc::Arcade::gameLoop()
{
	runGame = true;
	updateLib();
	while (runGame)
	{
		auto events = libs[idxLib]->getEvents();
		useEvents(events);
		libs[idxLib]->display();
		if (displayState == IDisplayModule::State::GAME) {
			if (games[idxGames]->update(events))
				goBackToTheMenu();
		}
	}
	libs[idxLib]->stop();
	scoreManager.addScore(games[idxGames]->getName(), menu.getName(), games[idxGames]->getScore());
	closeLibs();
}

void arc::Arcade::useEvents(const std::vector<arc::IGame::Event> &events)
{
	for (arc::IGame::Event event : events)
	{
		if (event == arc::IGame::EXIT)
			runGame = false;
		if (mapEvents.count(event))
			(*this.*mapEvents[event])();
	}
}

void arc::Arcade::nextGame()
{
	libs[idxLib]->stop();
	++idxGames;
	if (games.size() == idxGames)
		idxGames = 0;
	games[idxGames]->init();
	updateLib();
}

void arc::Arcade::previousGame()
{
	libs[idxLib]->stop();
	if (idxGames == 0)
		idxGames = games.size() - 1;
	else
		--idxGames;
	games[idxGames]->init();
	updateLib();
}

void arc::Arcade::nextLib()
{
	libs[idxLib]->stop();
	++idxLib;
	if (libs.size() == idxLib)
		idxLib = 0;
	updateLib();
}

void arc::Arcade::previousLib()
{
	libs[idxLib]->stop();
	if (idxLib == 0)
		idxLib = libs.size() - 1;
	else
		--idxLib;
	updateLib();
}

void arc::Arcade::setMenuStrings()
{
	std::vector<std::string> gameNames;
	std::vector<std::string> libNames;

	for (const auto &i : this->libs)
		libNames.push_back(i.get()->getName());
	for (const auto &i : this->games)
		gameNames.push_back(i.get()->getName());
	menu.setLibs(libNames);
	menu.setGames(gameNames);
}

void arc::Arcade::updateLib()
{
	if (displayState == IDisplayModule::State::MENU)
		libs[idxLib]->setMenu(&menu);
	else
		libs[idxLib]->setGame((games[idxGames].get()));
	menu.setScores(scoreManager.getTopScore(menu.getGames()));
	libs[idxLib]->setState(displayState);
	libs[idxLib]->init();
}

void arc::Arcade::closeLibs()
{
	for (auto &i : libs)
	{
		i.release();
	}
	for (auto &i : games)
	{
		i.release();
	}
	for (auto *dlloader : loaders)
		delete dlloader;
}

void arc::Arcade::downMenuAction()
{
	if (menu.getState() == IMenu::GAME)
		menu.setGamesIdx(menu.getGamesIdx() + 1);
	else if (menu.getState() == IMenu::LIBRARY)
		menu.setLibIdx(menu.getLibIdx() + 1);
}

void arc::Arcade::upMenuAction()
{
	if (menu.getState() == IMenu::GAME)
		menu.setGamesIdx(menu.getGamesIdx() - 1);
	else if (menu.getState() == IMenu::LIBRARY)
		menu.setLibIdx(menu.getLibIdx() - 1);
}

void arc::Arcade::enterMenuAction()
{
	if (displayState == IDisplayModule::MENU && menu.getState() == IMenu::LIBRARY)
	{
		libs[idxLib]->stop();
		displayState = IDisplayModule::GAME;
		idxLib = menu.getLibIdx();
		idxGames = menu.getGamesIdx();
		games[idxGames]->init();
		updateLib();
	}
	else
	{
		switch (menu.getState())
		{
			case IMenu::PLAYER:
				if (menu.getName().size() != 0)
					menu.setState(IMenu::GAME);
				break;
			case IMenu::GAME:
				menu.setState(IMenu::LIBRARY);
			default:
				break;
		}
	}
}

void arc::Arcade::returnMenuAction()
{
	switch (menu.getState())
	{
		case IMenu::LIBRARY:
			menu.setState(IMenu::GAME);
			break;
		case IMenu::GAME:
			menu.setState(IMenu::PLAYER);
		default:
			break;
	}
}

void arc::Arcade::goBackToTheMenu()
{
	if (displayState == IDisplayModule::GAME)
	{
		scoreManager.addScore(games[idxGames]->getName(), menu.getName(), games[idxGames]->getScore());
		displayState = IDisplayModule::MENU;
		menu.setState(IMenu::PLAYER);
		libs[idxLib]->stop();
		updateLib();
	}
}

void arc::Arcade::resetGame()
{
	games[idxGames]->init();
}

void arc::Arcade::initMapEvents()
{
	mapEvents[IGame::DOWN] = &Arcade::downMenuAction;
	mapEvents[IGame::UP] = &Arcade::upMenuAction;
	mapEvents[IGame::RETURN] = &Arcade::returnMenuAction;
	mapEvents[IGame::ENTER] = &Arcade::enterMenuAction;
	mapEvents[IGame::MENU] = &Arcade::goBackToTheMenu;
	mapEvents[IGame::RESET] = &Arcade::resetGame;
	mapEvents[IGame::NEXTGAME] = &Arcade::nextGame;
	mapEvents[IGame::PREVGAME] = &Arcade::previousGame;
	mapEvents[IGame::NEXTLIB] = &Arcade::nextLib;
	mapEvents[IGame::PREVLIB] = &Arcade::previousLib;
}
