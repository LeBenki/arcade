/*
** EPITECH PROJECT, 2018
** arc::AEntity.cpp
** File description:
** Abstract class Entity implementation
*/

#include "AEntity.hpp"

arc::AEntity::AEntity(const std::string &name)
{
	_name = name;
	_health = 100;
	_animationStatus = 0;
	_pos = {0.5, 0.5};
	_direction = DIR_UNDEFINED;
	_nextDirection = DIR_UNDEFINED;
}

const std::string &arc::AEntity::getName() const
{
	return _name;
}

void arc::AEntity::setName(const std::string &name)
{
	_name = name;
}
int arc::AEntity::getHealth() const
{
	return _health;
}

void arc::AEntity::setHealth(const int &health)
{
	_health = health;
}

int arc::AEntity::getAnimationStatus() const
{
	return _animationStatus;
}

void arc::AEntity::setAnimationStatus(const int &animation)
{
	_animationStatus = animation;
}

arc::posf_t arc::AEntity::getPos() const
{
	return _pos;
}

void arc::AEntity::setPos(const posf_t &pos)
{
	_pos = {pos.x, pos.y};
	if (_direction == DIR_DOWN || _direction == DIR_UP) {
		_pos.x = (int)_pos.x + 0.5;
	}
	else if (_direction == DIR_RIGHT || _direction == DIR_LEFT) {
		_pos.y = (int)_pos.y + 0.5;
	}
}

arc::Direction arc::AEntity::getDirection() const
{
	return _direction;
}

void arc::AEntity::setDirection(const Direction &direction)
{
	_direction = direction;
}

arc::Direction arc::AEntity::getNextDirection() const
{
	return _nextDirection;
}

void arc::AEntity::setNextDirection(const Direction &direction)
{
	_nextDirection = direction;
}

arc::Direction getOppositeDir(const arc::Direction &dir)
{
	switch (dir) {
		case arc::DIR_DOWN:
			return arc::DIR_UP;
		case arc::DIR_UP:
			return arc::DIR_DOWN;
		case arc::DIR_LEFT:
			return arc::DIR_RIGHT;
		case arc::DIR_RIGHT:
			return arc::DIR_LEFT;
		default:
			return arc::DIR_UNDEFINED;
	}
}