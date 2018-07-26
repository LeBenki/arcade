/*
** EPITECH PROJECT, 2018
** Spaceship.cpp
** File description:
** Spaceship class implementation for Solarfox
*/

#include "Spaceship.hpp"

arc::Spaceship::Spaceship(const int &x, const int &y, const int &level)
: ASolarFoxEntity("Spaceship", x, y)
{
	_speed = 0.15 * 1 + (level * 0.05);
	_cooldown = 300;
	_health = 1;
	_level = level;
}

void arc::Spaceship::spawnProjectile(std::vector<ASolarFoxEntity *> &entities)
{
	ASolarFoxEntity *entity = new Laser(_pos.x, _pos.y, _level);

	entity->setPos(_pos);
	entity->setDirection(_direction);
	entities.push_back(entity);
}


bool arc::Spaceship::isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities) const
{
	(void)entities;
	if (_pos.x < 0 || _pos.y < 0
		|| _pos.x >= map[0].size() || _pos.y >= map.size()
		|| map[_pos.y][_pos.x] == '#')
		return true;
	for (ASolarFoxEntity *ship : entities)
		if (ship->getName() == "Missile"
			&& ABS(DIST(_pos, ship->getPos())) < 0.5) {
			return true;
		}
	return false;
}

void arc::Spaceship::interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score)
{
	(void)map;
	(void)ships;
	(void)score;
}