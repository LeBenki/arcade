/*
** EPITECH PROJECT, 2018
** APacmanEntity.hpp
** File description:
** PacmanEntity abstract class implementation
*/

#ifndef APACMANENTITY_HPP_
	#define APACMANENTITY_HPP_

#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include "AEntity.hpp"

#define ANIMATION_FREQUENCY (float)100

namespace arc
{
	class APacmanEntity : public AEntity
	{
	public:
		APacmanEntity(const std::string &name);
		const std::vector<std::vector<int>> &getDistances() const;
		void calcDistances(const std::vector<std::string> &map,
					posf_t pos, int dist);
		void initDistances(const std::vector<std::string> &map);
		arc::posf_t getNextTile(const posf_t &pos,
					const Direction &dir,
					const std::vector<std::string> &map);
		void setAbsolutePos(posf_t &pos,
				const std::vector<std::string> &map);
		virtual void findPath(std::vector<std::vector<int>> distances,
				const std::vector<std::string> &map,
				const bool mode);
		void move(const std::vector<std::string> &map);
		virtual void updateAnimation(const std::vector<std::string> &map) = 0;
		void die();
		void revive();
		void centerPos();
		bool isAtSpawn() const;

	protected:
		float _speed;
		std::vector<std::vector<int>> _distances;
		unsigned int _id;
		std::chrono::milliseconds _lastUpdate;
	};
}

#endif /* !APACMANENTITY_HPP_ */
