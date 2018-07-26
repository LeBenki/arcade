/*
** EPITECH PROJECT, 2018
** ANibbler.cpp
** File description:
** ANibbler.cpp
*/

#include "ANibbler.hpp"

arc::ANibbler::ANibbler(const std::string &name, const int &x, const int &y)
: arc::AEntity(name)
{
	_pos = {(float)(x + 0.5), (float)(y + 0.5)};
	_health = 1;
	_moves = 0;
}

void arc::ANibbler::move()
{
	_moves++;
	switch (_direction) {
		case DIR_DOWN:
			_pos.y += NIBBLERSPEED;
			break;
		case DIR_UP:
			_pos.y -= NIBBLERSPEED;
			break;
		case DIR_LEFT:
			_pos.x -= NIBBLERSPEED;
			break;
		case DIR_RIGHT:
			_pos.x += NIBBLERSPEED;
			break;
		default:
			break;
	}
	_animationStatus = (_animationStatus + 1) % 3;
}

int arc::ANibbler::getMoves() const
{
	return _moves;
}

void arc::ANibbler::setMoves(const int &moves)
{
	_moves = moves;
}

void arc::ANibbler::justifyPos()
{
	if (_direction == DIR_UP || _direction == DIR_DOWN)
		_pos.x = floor(_pos.x) + 0.5;
	else if (_direction == DIR_LEFT || _direction == DIR_RIGHT)
		_pos.y = floor(_pos.y) + 0.5;
}