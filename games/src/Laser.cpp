/*
** EPITECH PROJECT, 2018
** Laser.cpp
** File description:
** Laser class implementation for Solarfox
*/

#include "Laser.hpp"

arc::Laser::Laser(const int &x, const int &y, const int &_level)
: ASolarFoxEntity("Laser", x, y)
{
	_speed = 0.3 * (1 + _level * 0.05);
	_range = 6;
}

void arc::Laser::spawnProjectile(std::vector<ASolarFoxEntity *> &entities)
{
	(void)entities;
	return;
}

bool arc::Laser::isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities) const
{
	(void)map;
	(void)entities;
	if (_speed * _moves > _range)
		return true;
	return false;
}


void arc::Laser::interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score)
{
	(void)ships;
	if (_pos.x < 0 || _pos.x >= map[0].size()
		|| _pos.y < 0 || _pos.y >= map.size())
		return;
	if (map[_pos.y][_pos.x] == '.') {
		map[_pos.y][_pos.x] = ' ';
		*score += 1;
	}
}