/*
** EPITECH PROJECT, 2018
** Pacman.hpp
** File description:
** Pacman entity header file
*/

#ifndef PACMAN_HPP_
	#define PACMAN_HPP_

#include "APacmanEntity.hpp"
#define PACMANSPEED 0.06

namespace arc
{
	class Pacman : public APacmanEntity
	{
	public:
		Pacman(const pos_t &pos, const unsigned int level);
		void updateAnimation(const std::vector<std::string> &map)
								override;
	};
}

#endif /* !PACMAN_HPP_ */
