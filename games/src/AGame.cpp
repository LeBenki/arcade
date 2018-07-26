/*
** EPITECH PROJECT, 2018
** arc::AGame.cpp
** File description:
** Abstract class game implementation
*/

#include "AGame.hpp"

arc::AGame::AGame(const std::string &name)
{
	_name = name;
	_score = 0;
	_time = 0;
	_entities = std::vector<IEntity *>();
}

void arc::AGame::init()
{
	for (IEntity *entity : _entities) {
		delete(entity);
	}
	_score = 0;
	_time = 0;
	loadMap("");
}

const std::string &arc::AGame::getName() const
{
	return _name;
}

void arc::AGame::setName(const std::string &name)
{
	_name = name;
}

const std::vector<std::string> &arc::AGame::getMap() const
{
	return _map;
}

void arc::AGame::setMap(const std::vector<std::string> &map)
{
	_map = map;
}

long arc::AGame::getScore() const
{
	return _score;
}

void arc::AGame::setScore(const long score)
{
	_score = score;
}

std::vector<arc::IEntity *> &arc::AGame::getEntities()
{
	return _entities;
}

void arc::AGame::setEntities(const std::vector<IEntity *> &entities)
{
	_entities = entities;
}