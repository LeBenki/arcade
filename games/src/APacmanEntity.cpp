/*
** EPITECH PROJECT, 2018
** APacmanEntity.cpp
** File description:
**
*/

#include "APacmanEntity.hpp"

arc::APacmanEntity::APacmanEntity(const std::string &name) : AEntity(name)
{
	_lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
}

void arc::APacmanEntity::setAbsolutePos(posf_t &pos,
				const std::vector<std::string> &map)
{
	if (pos.x >= map[0].size())
		pos.x -= map[0].size();
	else if (pos.x < 0)
		pos.x += map[0].size();
	if (pos.y >= map.size())
		pos.y -= map.size();
	else if (pos.y < 0)
		pos.y += map.size();
}

arc::posf_t arc::APacmanEntity::getNextTile(const posf_t &pos,
					const Direction &dir,
					const std::vector<std::string> &map)
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
	setAbsolutePos(posTo, map);
	return (posTo);
}

void arc::APacmanEntity::calcDistances(const std::vector<std::string> &map,
					posf_t posFrom, int dist)
{
	posf_t pos;

	if (dist == 0)
		_distances[posFrom.y][posFrom.x] = 0;
	for (int i = 1; i < 5; i++) {
		pos = getNextTile(posFrom, (Direction)i, map);
		if (_distances[pos.y][pos.x] != -2
			&& (_distances[pos.y][pos.x] == -1
				|| _distances[pos.y][pos.x] > dist)) {
			_distances[pos.y][pos.x] = dist + 1;
			calcDistances(map, pos, dist + 1);
		}
	}
}

void arc::APacmanEntity::initDistances(const std::vector<std::string> &map)
{
	std::vector<int> buffer;

	_distances.clear();
	for (const std::string &line : map) {
		for (const char c : line)
			buffer.push_back(c == '#' ? -2 : -1);
		_distances.push_back(buffer);
		buffer.clear();
	}
	calcDistances(map, _pos, 0);
}

void arc::APacmanEntity::findPath(std::vector<std::vector<int>> distances,
				const std::vector<std::string> &map,
				const bool mode)
{
	(void)distances;
	(void)map;
	(void)mode;
	return;
}

void arc::APacmanEntity::centerPos()
{
	if (_direction == DIR_DOWN || _direction == DIR_UP)
		_pos.x = floor(_pos.x) + 0.5;
	else if  (_direction == DIR_RIGHT || _direction == DIR_LEFT)
		_pos.y = floor(_pos.y) + 0.5;
}

void arc::APacmanEntity::move(const std::vector<std::string> &map)
{
	switch (_direction) {
		case DIR_DOWN:
			_pos.y += _speed;
			break;
		case DIR_UP:
			_pos.y -= _speed;
			break;
		case DIR_RIGHT:
			_pos.x += _speed;
			break;
		case DIR_LEFT:
			_pos.x -= _speed;
			break;
		default:
			return;
	};
	setAbsolutePos(_pos, map);
	centerPos();
	updateAnimation(map);
}

void arc::APacmanEntity::die()
{
	_name = "Eyes";
	_health = 0;
	_animationStatus = 2;
}

void arc::APacmanEntity::revive()
{
	_name = "Ghost" + std::to_string(_id % 4 + 1);
	_health = 1;
}

bool arc::APacmanEntity::isAtSpawn() const
{
	return (_distances[_pos.y][_pos.x] == 0);
}

const std::vector<std::vector<int>> &arc::APacmanEntity::getDistances() const
{
	return _distances;
}
