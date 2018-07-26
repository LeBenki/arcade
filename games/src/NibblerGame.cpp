/*
** EPITECH PROJECT, 2018
** arc::NibblerGame.cpp
** File description:
** Nibbler game class file
*/

#include "NibblerGame.hpp"

arc::NibblerGame::NibblerGame() : arc::AGame("nibbler")
{
	loadMap();
	_gameover = false;
}

void arc::NibblerGame::init()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
		delete _entities[i];
	_entities.clear();
	for (unsigned int i = 0; i < _player.size(); i++)
		delete _player[i];
	_player.clear();
	_movements.clear();
	_movements = std::vector<Direction>();
	loadMap("");
	_score = 0;
}

void arc::NibblerGame::validMapCheck()
{
	bool isFood = false;

	if (_map.size() == 0)
			throw arc::InvalidMap("The map has invalid format");
	for (const std::string &line : _map) {
		if (!line.size() || line.size() != _map[0].size())
			throw arc::InvalidMap("The map has invalid format");
	}
	for (const std::string &line : _map)
		for (const char c : line)
			if (c == 'o')
				isFood = true;
	if (_player.size() != 4)
		throw arc::InvalidMap("The map has invalid player spawn");
	else if (!isFood)
		throw arc::InvalidMap("The map has no food");
}

void arc::NibblerGame::loadMap(const std::string &path)
{
	std::ifstream stream(MAP_PATH + path);
	std::string line;

	if (path == "") {
		_map = _cachedMap;
		for (unsigned int i = 0; i < _map.size(); i++) {
			initEntities(_map[i], i);
			for (char &c : _map[i]) {
				if (c == 'P')
					c = ' ';
			}
		}
		validMapCheck();
		return;
	}
	if (!stream.is_open()) {
		//throw FileNotFoundException;
	}
	for (int i = 0; getline(stream, line); i++) {
		_cachedMap.push_back(line);
	}
}

void arc::NibblerGame::initEntities(const std::string &line, const int &y)
{
	for (unsigned int i = 0; i < line.size(); i++) {
		switch (line[i]) {
			case 'P':
				if (_player.size() > 0) {
					//throw exception invalid map
				}
				_player.push_back(
						new NibblerHead({(int)i, y}));
				_player.push_back(
						new NibblerBody({(int)i, y}));
				_player.push_back(
						new NibblerBody({(int)i, y}));
				_player.push_back(
						new NibblerTail({(int)i, y}));
				break;
			default:
				break;
		}
	}
}

void arc::NibblerGame::rotatePlayer()
{
	if (_player[0]->getNextDirection()
		== getOppositeDir(_player[0]->getDirection()))
		_player[0]->setNextDirection(DIR_UNDEFINED);
	if (_player[0]->getNextDirection()
		&& possibleMovement(_player[0]->getPos(),
				_player[0]->getNextDirection(),
				1)) {
		_player[0]->setDirection(_player[0]->getNextDirection());
		_player[0]->setNextDirection(DIR_UNDEFINED);
	}
}

void arc::NibblerGame::stuckCheck()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (!possibleMovement(_player[0]->getPos(), _player[0]->getDirection(),
						NIBBLERSPEED)) {
		if (time.tv_usec - _stuck.tv_usec > 200000)
			_gameover = true;
	}
	else
		gettimeofday(&_stuck, NULL);
}

bool arc::NibblerGame::update(const std::vector<Event> &events)
{
	processEvents(events);
	rotatePlayer();
	stuckCheck();
	movePlayer();
	//Tickrate control
	usleep(20000);
	if (_gameover) {
		_gameover = false;
		return true;
	}
	return false;
}

void arc::NibblerGame::processEvents(const std::vector<Event> &events)
{
	for (Event event : events) {
		switch (event) {
			case UP:
				_player[0]->setNextDirection(DIR_UP);
				break;
			case DOWN:
				_player[0]->setNextDirection(DIR_DOWN);
				break;
			case RIGHT:
				_player[0]->setNextDirection(DIR_RIGHT);
				break;
			case LEFT:
				_player[0]->setNextDirection(DIR_LEFT);
				break;
			case JUMP:
				for (ANibbler *player : _player) {
					std::cout << player->getPos().x << " " << player->getPos().y;
					std::cout << " m: " << player->getMoves() << " | ";
				}
				std::cout << std::endl;
				std::cout << "moves: " << _movements.size() << std::endl;
				spawnFood();
				break;
			default:
				break;
		}
	}
}

arc::posf_t arc::NibblerGame::getNextPos(const posf_t &pos,
					const Direction &dir,
					const float &speed) const
{
	posf_t posTo = pos;

	switch (dir) {
		case DIR_DOWN:
			posTo.y += speed;
			break;
		case DIR_UP:
			posTo.y -= speed;
			break;
		case DIR_LEFT:
			posTo.x -= speed;
			break;
		case DIR_RIGHT:
			posTo.x += speed;
			break;
		default:
			break;
	}
	return posTo;
}

bool arc::NibblerGame::possibleMovement(const posf_t &pos, const Direction &dir,
						const float &speed) const
{
	posf_t posTo = getNextPos(pos, dir, speed + 0.001);

	if (posTo.x < 0 || posTo.x >= _map[0].size()
		|| posTo.y < 0 || posTo.y >= _map.size()
		|| _map[posTo.y][posTo.x] == '#') {
		return (false);
	}
	return (true);
}

void arc::NibblerGame::clearMovements()
{
	int movementsNb = MOVES_PER_SECTION;

	if (_movements.size() > 100 + movementsNb * _player.size()) {
		_movements.erase(_movements.begin(),
			_movements.begin() + 1);
		for (arc::ANibbler *player: _player)
			player->setMoves(player->getMoves() - 1);
	}
}

void arc::NibblerGame::movePlayer()
{
	if (_player[0]->getDirection() == DIR_UNDEFINED
		|| !possibleMovement(_player[0]->getPos(),
					_player[0]->getDirection(),
					NIBBLERSPEED)) {
		return;
	}
	for (int i = _player.size() - 1; i >= 0; i--) {
		if (i > 0) {
			if ((int)_movements.size() - 1
				< i * (float)1 / NIBBLERSPEED)
				continue;
			_player[i]->setDirection(_movements[_player[i]
				->getMoves()]);
		}
		_player[i]->move();
		_player[i]->justifyPos();
	}
	_movements.push_back(_player[0]->getDirection());
	clearMovements();
	interact();
}

void arc::NibblerGame::growPlayer()
{
	posf_t newPos;
	ANibbler *tail = _player[_player.size() - 1];
	ANibbler *newPart;

	newPos = getNextPos(tail->getPos(),
				getOppositeDir(tail->getDirection()), 1);
	newPart = new NibblerBody(tail->getPos().x, tail->getPos().y);
	newPart->setPos(tail->getPos());
	newPart->setMoves(tail->getMoves());
	for (int i = 0; i < _player[0]->getMoves()
		- _player[1]->getMoves(); i++) {
		tail->setDirection(getOppositeDir(_movements[tail->getMoves()
									- i]));
		tail->move();
		tail->setMoves(tail->getMoves() - 1);
	}
	tail->setMoves(newPart->getMoves() - (_player[0]->getMoves()
						- _player[1]->getMoves()));
	newPart->setDirection(tail->getDirection());
	_player.insert(_player.end() - 1, newPart);
}

void arc::NibblerGame::interact()
{
	posf_t playerPos = _player[0]->getPos();

	if (_map[playerPos.y][playerPos.x] == 'o') {
		growPlayer();
		_map[playerPos.y][playerPos.x] = ' ';
		spawnFood();
		_score += 20;
	}
	for (unsigned int i = 1; i < _player.size(); i++) {
		if (i > 1 && _player[0]->getMoves() > MOVES_PER_SECTION
			&& abs(DIST(playerPos, _player[i]->getPos()))
			< NIBBLERSPEED) {
			sleep(1);
			_gameover = true;
		}
	}
}

void arc::NibblerGame::spawnFood()
{
	pos_t pos;
	posf_t playerPos;
	bool empty = false;
	int start = time(NULL);

	srand(time(NULL));
	while (true) {
		if (time(NULL) - start >= 1)
			break;
		empty = false;
		pos = (pos_t){(int)(rand() % _map[0].size()),
				(int)(rand() % _map.size())};
		for (int i = 1; i < 5; i++) {
			if (possibleMovement((posf_t){(float)(pos.x + 0.5),
				(float)(pos.y + 0.5)}, (arc::Direction)i, 1)) {
				empty = true;
				break;
			}
		}
		for (ANibbler *playerPart : _player) {
			playerPos = playerPart->getPos();
			if (pos.x == floor(playerPos.x)
				&& pos.y == floor(playerPos.y)) {
				empty = false;
				break;
			}
		}
		if (empty && _map[pos.y][pos.x] == ' ') {
			_map[pos.y][pos.x] = 'o';
			break;
		}
	}
}

std::vector<arc::IEntity *> &arc::NibblerGame::getEntities()
{
	ret.clear();
	for (IEntity *entity : _player) {
		ret.insert(ret.begin(), entity);
	}
	return ret;
}

extern "C" arc::IGame *getInstance()
{
	return new arc::NibblerGame();
}