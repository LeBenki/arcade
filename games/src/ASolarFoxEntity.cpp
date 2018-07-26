/*
** EPITECH PROJECT, 2018
** ASolarFoxEntity.cpp
** File description:
** SolarFox entity abstract class implementation
*/

#include "ASolarFoxEntity.hpp"

arc::ASolarFoxEntity::ASolarFoxEntity(const std::string &name,
					const int &x,
					const int &y)
					: AEntity(name)
{
	_pos = (posf_t){(float)(x + 0.5), (float)(y + 0.5)};
	_cooldownStatus = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
	_speed = 0.5;
	_moves = 0;
	_range = 0;
	_cooldown = 2000.0;
	_level = 0;
}

void arc::ASolarFoxEntity::shoot(std::vector<ASolarFoxEntity *> &entities)
{
	std::chrono::milliseconds now = std::chrono::duration_cast<
		std::chrono::milliseconds>(std::chrono::system_clock::now()
		.time_since_epoch());

	if (now.count() - _cooldownStatus.count() > _cooldown) {
		_cooldownStatus = now;
		this->spawnProjectile(entities);
	}
}

void arc::ASolarFoxEntity::rotate(const pos_t &mapsize)
{
	(void)mapsize;
	if (_nextDirection == DIR_UNDEFINED
		|| _nextDirection == getOppositeDir(_direction)) {
		_nextDirection = DIR_UNDEFINED;
		return;
	}
	_direction = _nextDirection;
	_nextDirection = DIR_UNDEFINED;
}

void arc::ASolarFoxEntity::move()
{
	switch (_direction) {
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
	_moves++;
	_animationStatus = _animationStatus + 1 > 2 ? 0 : _animationStatus + 1;
}

const float &arc::ASolarFoxEntity::getSpeed() const
{
	return _speed;
}