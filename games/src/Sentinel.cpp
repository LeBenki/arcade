/*
** EPITECH PROJECT, 2018
** sentinel.cpp
** File description:
** Sentinel class implementation for Solarfox
*/

#include "Sentinel.hpp"

arc::Sentinel::Sentinel(const int &x, const int &y, const int &level)
: ASolarFoxEntity("Sentinel", x, y)
{
	_speed = 0.1 * 1 + (level * 0.02);
	_level = level;
	_cooldown = 2000.0 / (1 + level * 0.2);
}

void arc::Sentinel::spawnProjectile(std::vector<ASolarFoxEntity *> &entities)
{
	ASolarFoxEntity *entity = new Missile(_pos.x, _pos.y, _level);

	entity->setPos(_pos);
	entity->setDirection(_direction);
	entities.push_back(entity);
}

void arc::Sentinel::move()
{
	switch (_nextDirection) {
		case DIR_UP:
			_pos.y -= _speed;
			break;
		case DIR_DOWN:
			_pos.y += _speed;
			break;
		case DIR_RIGHT:
			_pos.x += _speed;
			break;
		case DIR_LEFT:
			_pos.x -= _speed;
			break;
		default:
			break;
	}
	_animationStatus = _animationStatus + 1 > 2 ? 0 : _animationStatus + 1;
}

void arc::Sentinel::rotate(const pos_t &mapsize)
{
	if (_pos.x < 0 || _pos.y < 0
		|| _pos.x >= mapsize.x || _pos.y >= mapsize.y) {
		_nextDirection = getOppositeDir(_nextDirection);
	}
}

bool arc::Sentinel::isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities) const
{
	(void)map;
	(void)entities;
	return false;
}

void arc::Sentinel::interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score)
{
	posf_t playerPos = ships[0]->getPos();

	(void)score;
	(void)map;
	if (ABS(playerPos.x - _pos.x) <= 1.5
		|| ABS(playerPos.y - _pos.y) <= 1.5) {
		shoot(ships);
	}
}
