/*
** EPITECH PROJECT, 2018
** Ghost.hpp
** File description:
** Ghost entity header file
*/

#ifndef GHOST_HPP_
	#define GHOST_HPP_

#include "APacmanEntity.hpp"
#define GHOSTSPEED 0.03

namespace arc
{
	class Ghost : public APacmanEntity
	{
	public:
		Ghost(const pos_t &pos,
			const unsigned int level,
			const unsigned int id);
		void findPath(std::vector<std::vector<int>> distances,
				const std::vector<std::string> &map,
				const bool mode) override;
		void updateAnimation(const std::vector<std::string> &map)
								override;
	};
}

#endif /* !GHOST_HPP_ */
