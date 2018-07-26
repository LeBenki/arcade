/*
** EPITECH PROJECT, 2018
** Missile.cpp
** File description:
** Missile class implementation for Solarfox
*/

#include "Missile.hpp"

arc::Missile::Missile(const int &x, const int &y, const int &level)
: ASolarFoxEntity("Missile", x, y)
{
	_speed = 0.1 * 1 + (level * 0.1);
	_range = 50;
	_level = level;
}

void arc::Missile::spawnProjectile(std::vector<ASolarFoxEntity *> &entities)
{
	(void)entities;
	return;
}

bool arc::Missile::isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities) const
{
	(void)map;
	if (_pos.x < 0 || _pos.x >= map[0].size()
		|| _pos.y < 0 || _pos.y >= map.size()
		|| _speed * _moves > _range)
		return true;
	for (ASolarFoxEntity *ship : entities)
		if (ship->getName() == "Laser"
			&& ABS(DIST(_pos, ship->getPos())) < 1) {
			return true;
		}
	return false;
}

void arc::Missile::interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score)
{
	(void)ships;
	(void)map;
	(void)score;
}