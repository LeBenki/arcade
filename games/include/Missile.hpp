/*
** EPITECH PROJECT, 2018
** Missile.hpp
** File description:
** SolarFox Missile entity header
*/

#ifndef MISSILE_HPP_
	#define MISSILE_HPP_

#include "ASolarFoxEntity.hpp"

namespace arc
{
	class Missile : public ASolarFoxEntity
	{
	public:
		Missile(const int &x, const int &y, const int &level);
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

#endif /* !MISSILE_HPP_ */
