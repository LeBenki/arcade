/*
** EPITECH PROJECT, 2018
** Laser.hpp
** File description:
** SolarFox Laser entity header
*/

#ifndef LASER_HPP_
	#define LASER_HPP_

#include "ASolarFoxEntity.hpp"
#include "Missile.hpp"

namespace arc
{
	class Laser : public ASolarFoxEntity
	{
	public:
		Laser(const int &x, const int &y, const int &level);
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

#endif /* !LASER_HPP_ */
