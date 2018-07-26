/*
** EPITECH PROJECT, 2018
** Sentinel.hpp
** File description:
** SolarFox Sentinel entity header
*/

#ifndef SENTINEL_HPP_
	#define SENTINEL_HPP_

#include "ASolarFoxEntity.hpp"
#include "Missile.hpp"

namespace arc
{
	class Sentinel : public ASolarFoxEntity
	{
	public:
		Sentinel(const int &x, const int &y, const int &level);
		void spawnProjectile(std::vector<ASolarFoxEntity *>
					&entities) override;
		void rotate(const pos_t &mapsize) override;
		void move() override;
		bool isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities)
								const override;
		void interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score) override;
	};
}

#endif /* !SENTINEL_HPP_ */
