/*
** EPITECH PROJECT, 2018
** arc::AMenu
** File description:
** Implementation of arc::AMenu
*/

#include "AMenu.hpp"

arc::AMenu::AMenu() : gamesIdx(0), libIdx(0), state(IMenu::PLAYER), name("")
{}

arc::AMenu::~AMenu() = default;

const std::vector<std::string> &arc::AMenu::getLibs() const
{
	return libs;
}

const std::vector<std::string> &arc::AMenu::getGames() const
{
	return games;
}

int arc::AMenu::getLibIdx() const
{
	return libIdx;
}

int arc::AMenu::getGamesIdx() const
{
	return gamesIdx;
}

void arc::AMenu::setLibs(const std::vector<std::string> &libs)
{
	this->libs = libs;
}

void arc::AMenu::setGames(const std::vector<std::string> &games)
{
	this->games = games;
}

void arc::AMenu::setLibIdx(int idx)
{
	this->libIdx = idx;
	if (libIdx >= (int)libs.size())
		this->libIdx = 0;
	else if (libIdx < 0)
		this->libIdx = libs.size() - 1;
}

void arc::AMenu::setGamesIdx(int idx)
{
	this->gamesIdx = idx;
	if (gamesIdx >= (int)games.size())
		this->gamesIdx = 0;
	else if (gamesIdx < 0)
		this->gamesIdx = games.size() - 1;
}

arc::IMenu::State arc::AMenu::getState() const
{
	return state;
}

void arc::AMenu::setState(State state)
{
	this->state = state;
}

const std::string &arc::AMenu::getName() const
{
	return name;
}

void arc::AMenu::setName(const std::string &name)
{
	AMenu::name = name;
}

void arc::AMenu::setScores(const std::map<std::string, std::vector<std::string>> &s)
{
	scores = s;
}

const std::map<std::string, std::vector<std::string>> &arc::AMenu::getScores() const
{
	return scores;
}
