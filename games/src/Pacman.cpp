/*
** EPITECH PROJECT, 2018
** Pacman.cpp
** File description:
** Pacman entity class file
*/

#include "Pacman.hpp"

arc::Pacman::Pacman(const pos_t &pos, const unsigned int level)
: APacmanEntity("Pacman")
{
	_pos = {(float)(pos.x + 0.5), (float)(pos.y + 0.5)};
	_health = 3;
	_speed = PACMANSPEED * (1 + level * 0.5);
}

void arc::Pacman::updateAnimation(const std::vector<std::string> &map)
{
	std::chrono::milliseconds now = std::chrono::duration_cast<
		std::chrono::milliseconds>(std::chrono::system_clock::now()
		.time_since_epoch());

	if (now.count() - _lastUpdate.count() > ANIMATION_FREQUENCY
						/ (_speed / PACMANSPEED)) {
		_lastUpdate = now;
		initDistances(map);
		_animationStatus = _animationStatus + 1 > 2 ? 0
			: _animationStatus + 1;
	}
}