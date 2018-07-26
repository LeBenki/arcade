/*
** EPITECH PROJECT, 2018
** SolarFoxGame.cpp
** File description:
** SolarFox game implementation
*/

#include "SolarFoxGame.hpp"

arc::SolarFoxGame::SolarFoxGame() : AGame("solarfox")
{
	loadMap();
}

void arc::SolarFoxGame::init()
{
	for (unsigned int i = 0; i < _ships.size(); i++)
		delete _ships[i];
	_ships.clear();
	_score = 0;
	_level = 0;
	loadMap();
	loadMap("");
	_time = time(NULL);
}

void arc::SolarFoxGame::loadMap(const std::string &map)
{
	std::ifstream stream(MAP_PATH + map);
	std::string line;

	if (map == "") {
		_map = _cachedMap;
		for (unsigned int i = 0; i < _map.size(); i++) {
			for (char &c : _map[i]) {
				if (c == 'M' || c == 'P')
					c = ' ';
			}
		}
		initEntities();
		return;
	}
	_cachedMap = std::vector<std::string>();
	if (!stream.is_open()) {
		throw ResourceNotFound(MAP_PATH + map);
	}
	for (int i = 0; getline(stream, line); i++) {
		_cachedMap.push_back(line);
	}
}

void arc::SolarFoxGame::validMapCheck()
{
	bool isSolarCells = false;

	if (_map.size() == 0)
			throw arc::InvalidMap("The map has invalid format");
	for (const std::string &line : _map) {
		if (!line.size() || line.size() != _map[0].size())
			throw arc::InvalidMap("The map has invalid format");
	}
	for (const std::string &line : _map)
		for (const char c : line)
			if (c == '.')
				isSolarCells = true;
	else if (!isSolarCells)
		throw arc::InvalidMap("The map has no solar cells");
}

void arc::SolarFoxGame::initEntities()
{
	pos_t mapsize = (pos_t){(int)_cachedMap[0].size(),
				(int)_cachedMap.size()};

	_ships.push_back(new Spaceship(mapsize.x / 2, mapsize.y / 2, _level));
	_ships.push_back(new Sentinel(mapsize.x / 2, mapsize.y - 1, _level));
	_ships.push_back(new Sentinel(0, mapsize.y  / 2, _level));
	_ships.push_back(new Sentinel(mapsize.x / 2, 0, _level));
	_ships.push_back(new Sentinel(mapsize.x - 1, mapsize.y / 2, _level));
	_ships.push_back(new Missile(mapsize.x * 10, mapsize.y * 10, _level));
	_ships.push_back(new Laser(mapsize.x * 10, mapsize.y * 10, _level));
	for (int i = 1; i < 5; i++) {
		_ships[i]->setDirection((Direction)i);
		_ships[i]->setNextDirection((Direction)(i % 4 + 1));
	}
}

void arc::SolarFoxGame::destroyProjectiles()
{
	std::chrono::milliseconds now = std::chrono::duration_cast<
		std::chrono::milliseconds>(std::chrono::system_clock::now()
		.time_since_epoch());


	if (_ships[0]->isDestroyed(_map, _ships)) {
		sleep(1);
		return;
	}
	for (unsigned int i = 0; i < _ships.size(); i++) {
		if (_ships[i]->isDestroyed(_map, _ships)) {
			delete _ships[i];
			_ships.erase(_ships.begin() + i);
			i--;
		}
	}
}

void arc::SolarFoxGame::shipsRotation()
{
	for (ASolarFoxEntity *ship : _ships) {
		ship->rotate((pos_t){(int)_map[0].size(), (int)_map.size()});
	}
}

void arc::SolarFoxGame::shipsMovement()
{
	for (unsigned int i = 0; i < _ships.size(); i++) {
		_ships[i]->move();
		_ships[i]->interact(_map, _ships, &_score);
	}
}

void arc::SolarFoxGame::goalCheck()
{
	for (const std::string &line : _map)
		for (const char &c : line)
			if (c == '.')
				return;
	_level++;
	for (unsigned int i = 0; i < _ships.size(); i++)
		delete _ships[i];
	_ships.clear();
	try {
		loadMap(std::to_string(_level) + ".map");
		loadMap("");
	}
	catch (arc::ResourceNotFound &e) {
		loadMap();
		loadMap("");
	}
}

bool arc::SolarFoxGame::update(const std::vector<Event> &events)
{
	processEvents(events);
	shipsRotation();
	shipsMovement();
	destroyProjectiles();
	goalCheck();
	//Tickrate control
	usleep(20000);
	if (_ships[0]->isDestroyed(_map, _ships))
		return true;
	return false;
}

void arc::SolarFoxGame::processEvents(const std::vector<Event> &events)
{
	for (Event event : events) {
		switch (event) {
			case RIGHT:
				_ships[0]->setNextDirection(DIR_RIGHT);
				break;
			case LEFT:
				_ships[0]->setNextDirection(DIR_LEFT);
				break;
			case UP:
				_ships[0]->setNextDirection(DIR_UP);
				break;
			case DOWN:
				_ships[0]->setNextDirection(DIR_DOWN);
				break;
			case JUMP:
				_ships[0]->shoot(_ships);
				break;
			default:
				break;
		}
	}
}

std::vector<arc::IEntity *> &arc::SolarFoxGame::getEntities()
{
	ret.clear();
	for (IEntity *entity : _ships)
		ret.push_back(entity);
	return ret;
}

extern "C" arc::IGame *getInstance()
{
	return new arc::SolarFoxGame();
}