/*
** EPITECH PROJECT, 2018
** arc::PacmanGame.cpp
** File description:
** arc::PacmanGame class file
*/

#include "PacmanGame.hpp"

arc::PacmanGame::PacmanGame(const std::string &mapPath) : AGame("pacman")
{
	this->loadMap(mapPath);
	_gameover = false;
}

arc::PacmanGame::~PacmanGame()
{
}

void arc::PacmanGame::init()
{
	for (unsigned int i = 0; i < _pacmanEntities.size(); i++)
		delete _pacmanEntities[i];
	_pacmanEntities.clear();
	_score = 0;
	_enemies = 0;
	_buff = 0;
	_level = 0;
	_time = time(NULL);
	_liveTime = time(NULL);
	this->loadMap("");
}

void arc::PacmanGame::loadMap(const std::string &map)
{
	std::ifstream stream(MAP_PATH + map);
	std::string line;

	if (map == "") {
		_map = _cachedMap;
		for (unsigned int i = 0; i < _map.size(); i++) {
			initEntities(_map[i], i);
			for (char &c : _map[i]) {
				if (c == 'M' || c == 'P')
					c = ' ';
			}
		}
		validMapCheck();
		return;
	}
	if (!stream.is_open())
		throw arc::ResourceNotFound(MAP_PATH + map);
	for (int i = 0; getline(stream, line); i++)
		_cachedMap.push_back(line);
	_liveTime = time(NULL);
}

void arc::PacmanGame::validMapCheck()
{
	bool isPlayer = false;
	bool isEnemy = false;


	if (_map.size() == 0)
			throw arc::InvalidMap("The map has invalid format");
	for (const std::string &line : _map) {
		if (!line.size() || line.size() != _map[0].size())
			throw arc::InvalidMap("The map has invalid format");
	}
	for (IEntity *entity : _pacmanEntities) {
		if (entity->getName() == "Pacman" && isPlayer == false)
			isPlayer = true;
		else if (entity->getName() == "Pacman" && isPlayer == true)
			throw arc::InvalidMap("Too many players on this map");
		if (entity->getName() == "Ghost1"
			|| entity->getName() == "Ghost2"
			|| entity->getName() == "Ghost3"
			|| entity->getName() == "Ghost4")
			isEnemy = true;
	}
	if (!isPlayer || !isEnemy)
		throw arc::InvalidMap("The map has invalid entities");
}

void arc::PacmanGame::initEntities(const std::string &line, const int &y)
{
	for (unsigned int i = 0; i < line.size(); i++) {
		switch (line[i]) {
			case 'P':
				_pacmanEntities.insert(_pacmanEntities.begin(),
						new Pacman({(int)i, y},
								_level));
				_pacmanEntities[0]->initDistances(_map);
				break;
			case 'M':
				_pacmanEntities.push_back(new Ghost({(int)i, y},
							_level, _enemies));
				_pacmanEntities[_pacmanEntities.size() - 1]
							->initDistances(_map);
				_enemies++;
				break;
			default:
				break;
		}
	}
}

void arc::PacmanGame::setAbsolutePos(posf_t &pos)
{
	if (pos.x >= _map[0].size())
		pos.x -= _map[0].size();
	else if (pos.x < 0)
		pos.x += _map[0].size();
	if (pos.y >= _map.size())
		pos.y -= _map.size();
	else if (pos.y < 0)
		pos.y += _map.size();
}

bool arc::PacmanGame::isTileAccessible(const IEntity &entity, const posf_t &posFrom,
				const Direction &dir, const float &speed)
{
	posf_t posTo = posFrom;

	if (dir != DIR_UNDEFINED)
		dir == DIR_LEFT ? posTo.x -= speed :
		dir == DIR_RIGHT ? posTo.x += speed :
		dir == DIR_UP ? posTo.y -= speed :
		dir == DIR_DOWN ? posTo.y += speed : 0;
	setAbsolutePos(posTo);
	if (posTo.y < 0 || posTo.y > _map.size()
		|| posTo.x < 0 || posTo.x > _map[0].size()
		|| _map[posTo.y][posTo.x] == '#'
		|| (&entity == _pacmanEntities[0]
			&& _map[posTo.y][posTo.x] == '-')) {
		return false;
	}
	return true;
}

void arc::PacmanGame::checkPlayerRotation()
{
	IEntity *player = _pacmanEntities[0];

	if (player->getNextDirection() != DIR_UNDEFINED &&
		isTileAccessible(*player, player->getPos(),
					player->getNextDirection(), 1)) {
			player->setDirection(player->getNextDirection());
			player->setNextDirection(DIR_UNDEFINED);
	}
}

void arc::PacmanGame::randomPath(IEntity &entity)
{
	while (entity.getDirection() == DIR_UNDEFINED
		|| !isTileAccessible(entity, entity.getPos(),
					entity.getDirection(), 1)) {
		entity.setDirection((Direction)(random() % 4 + 1));
	}
}

void arc::PacmanGame::goalCheck()
{
	int livesBuff = _pacmanEntities[0]->getHealth();

	for (std::string &line : _map) {
		for (char &c : line)
			if (c == '.' || c == 'o')
				return;
	}

	for (unsigned int i = 0; i < _pacmanEntities.size(); i++)
		delete _pacmanEntities[i];
	_pacmanEntities.clear();
	_level++;
	loadMap("");
	_pacmanEntities[0]->setHealth(livesBuff);
}

void arc::PacmanGame::interact()
{
	posf_t playerPos = _pacmanEntities[0]->getPos();

	if (isTileAccessible(*_pacmanEntities[0], playerPos,
						DIR_UNDEFINED, 1)) {
		if (_map[playerPos.y][playerPos.x] == '.') {
			_score++;
		}
		else if (_map[playerPos.y][playerPos.x] == 'o') {
			_score += 5;
			_buff = time(NULL);
		}
		_map[playerPos.y][playerPos.x] = ' ';
		goalCheck();
	}
}

void arc::PacmanGame::updatePlayer()
{
	APacmanEntity *player = _pacmanEntities[0];

	checkPlayerRotation();
	if (isTileAccessible(*player, player->getPos(),
				player->getDirection(), (float)0.3))
		_pacmanEntities[0]->move(_map);
	interact();
}

void arc::PacmanGame::killPlayer()
{
	std::vector<std::string> mapBuffer = _map;
	int health = _pacmanEntities[0]->getHealth();

	if (health - 1 == 0) {
		_gameover = true;
	}
	for (unsigned int i = 0; i < _pacmanEntities.size(); i++)
		delete _pacmanEntities[i];
	_pacmanEntities.clear();
	loadMap("");
	for (unsigned int i = 0; i < _map.size(); i++) {
		for (unsigned int j = 0; j < _map[i].size(); j++)
			if (mapBuffer[i][j] == ' '
				&& (_map[i][j] == '.' || _map[i][j] == 'o'))
				_map[i][j] = ' ';
	}
	_pacmanEntities[0]->setHealth(health - 1);
}

void arc::PacmanGame::attack()
{
	posf_t a = _pacmanEntities[0]->getPos();
	posf_t b;

	for (unsigned int i = 1; i < _pacmanEntities.size(); i++) {
		b = _pacmanEntities[i]->getPos();
		if (time(NULL) - _buff < BUFFTIME && abs(DIST(a, b)) < 0.5) {
			_pacmanEntities[i]->die();
		}
		else if (abs(DIST(a, b)) < 0.5
			&& _pacmanEntities[i]->getHealth() > 0) {
			killPlayer();
		}
	}
}

void arc::PacmanGame::updateEnemies()
{
	for (unsigned int i = 1; i < _pacmanEntities.size(); i++) {
		if (time(NULL) - _liveTime >= 10 - _level * 1.5) {
			if (_pacmanEntities[i]->getHealth() == 0
				&& _pacmanEntities[i]->isAtSpawn())
				_pacmanEntities[i]->revive();
			if (i > 1 && _pacmanEntities[i]->getHealth() > 0
				&& random() % 50 != 0)
				randomPath(*_pacmanEntities[i]);
			else
				_pacmanEntities[i]->findPath(
					_pacmanEntities[0]->getDistances(),
					_map, time(NULL) - _buff < BUFFTIME
							? true : false);
			_pacmanEntities[i]->move(_map);
			if (time(NULL) - _buff < BUFFTIME)
				_pacmanEntities[i]->setAnimationStatus(2);
		}
	}
	attack();
}

bool arc::PacmanGame::update(const std::vector<Event> &events)
{
	processMovements(events);
	updatePlayer();
	updateEnemies();
	usleep(5000);
	if (_gameover) {
		_gameover = false;
		return true;
	}
	return false;
}

arc::posf_t arc::PacmanGame::getNextTile(const posf_t &pos, const Direction &dir)
{
	posf_t posTo = pos;

	switch (dir) {
		case DIR_DOWN:
			posTo.y += 1;
			break;
		case DIR_UP:
			posTo.y -= 1;
			break;
		case DIR_RIGHT:
			posTo.x += 1;
			break;
		case DIR_LEFT:
			posTo.x -= 1;
			break;
		default:
			break;
	};
	setAbsolutePos(posTo);
	return (posTo);
}

void arc::PacmanGame::processMovements(std::vector<Event> events)
{
	for (Event event : events)
	{
		switch (event)
		{
			case DOWN:
				_pacmanEntities[0]->setNextDirection(DIR_DOWN);
				break;
			case UP:
				_pacmanEntities[0]->setNextDirection(DIR_UP);
				break;
			case RIGHT:
				_pacmanEntities[0]->setNextDirection(DIR_RIGHT);
				break;
			case LEFT:
				_pacmanEntities[0]->setNextDirection(DIR_LEFT);
				break;
			case JUMP:
				break;
			default:
				break;
		}
	}
}

std::vector<arc::IEntity *> &arc::PacmanGame::getEntities()
{
	ret.clear();
	for (arc::IEntity *entity : _pacmanEntities)
		ret.push_back(entity);
	return ret;
}

extern "C" arc::IGame *getInstance()
{
	return new arc::PacmanGame();
}
