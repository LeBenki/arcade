/*
** EPITECH PROJECT, 2018
** Spaceship.hpp
** File description:
** Spaceship class header
*/

#ifndef SPACESHIP_HPP_
	#define SPACESHIP_HPP_

#include "ASolarFoxEntity.hpp"
#include "Laser.hpp"

namespace arc
{
	class Spaceship : public ASolarFoxEntity
	{
	public:
		Spaceship(const int &x, const int &y, const int &level);
		void spawnProjectile(std::vector<ASolarFoxEntity *>
					&entities) override;
		bool isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities)
								const override;
		void interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score) override;
	};
}

#endif /* !SPACESHIP_HPP_ */
