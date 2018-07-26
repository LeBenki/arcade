/*
** EPITECH PROJECT, 2018
** ASolarFoxEntity.cpp
** File description:
** SolarFox entity abstract class header
*/

#ifndef ASOLARFOXENTITY_HPP_
	#define ASOLARFOXENTITY_HPP_

#include <math.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include "AEntity.hpp"
#include "IGame.hpp"

namespace arc
{
	class ASolarFoxEntity : public AEntity
	{
	public:
		ASolarFoxEntity(const std::string &name,
				const int &x,
				const int &y);
		virtual void rotate(const pos_t &mapsize);
		virtual void move();
		const float &getSpeed() const;
		void shoot(std::vector<ASolarFoxEntity *> &entities);
		virtual void spawnProjectile(std::vector<ASolarFoxEntity *>
								&entities) = 0;
		virtual bool isDestroyed(const std::vector<std::string> &map,
			const std::vector<ASolarFoxEntity *> &entities)
								const = 0;
		virtual void interact(std::vector<std::string> &map,
				std::vector<ASolarFoxEntity *> &ships,
				int *score) = 0;

	protected:
		std::chrono::milliseconds _cooldownStatus;
		unsigned int _cooldown;
		float _speed;
		unsigned int _moves;
		unsigned int _range;
		unsigned int _level;
	};
}

#endif /* !ASOLARFOXENTITY_HPP_ */
