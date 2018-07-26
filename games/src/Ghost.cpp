/*
** EPITECH PROJECT, 2018
** Ghost.cpp
** File description:
** Ghost entity class file
*/

#include "Ghost.hpp"

arc::Ghost::Ghost(const arc::pos_t &pos,
	const unsigned int level, const unsigned int id)
: arc::APacmanEntity("Ghost" + std::to_string(id % 4 + 1))
{
	_pos = {(float)(pos.x + 0.5), (float)(pos.y + 0.5)};
	_health = 1;
	_speed = GHOSTSPEED * (1 + level * 0.5);
	_id = id;
}


void arc::Ghost::findPath(std::vector<std::vector<int>> distances,
				const std::vector<std::string> &map,
				const bool mode)
{
	Direction target = DIR_UNDEFINED;
	int dist = -1;
	posf_t posTo;

	for (int i = 1; i < 5; i++) {
		posTo = getNextTile(_pos, (arc::Direction)i, map);
		if (_health == 0 && _distances[posTo.y][posTo.x] != -2
			&& (dist == -1 || _distances[posTo.y][posTo.x] < dist))
		{
			target = (Direction)i;
			dist = _distances[posTo.y][posTo.x];
		}
		else if (_health > 0
			&& distances[posTo.y][posTo.x] != -2 && (dist == -1
				|| (mode) ? distances[posTo.y][posTo.x] > dist
					: distances[posTo.y][posTo.x] < dist))
		{
			target = (arc::Direction)i;
			dist = distances[posTo.y][posTo.x];
		}
	}
	_direction = target;
}

void arc::Ghost::updateAnimation(const std::vector<std::string> &map)
{
	std::chrono::milliseconds now = std::chrono::duration_cast<
		std::chrono::milliseconds>(std::chrono::system_clock::now()
		.time_since_epoch());

	(void)map;
	if (now.count() - _lastUpdate.count() > ANIMATION_FREQUENCY
						/ (_speed / GHOSTSPEED)) {
		_lastUpdate = now;
		_animationStatus = _animationStatus + 1 > 1 ? 0
			: _animationStatus + 1;
	}
}