/*
** EPITECH PROJECT, 2018
** AEntity.hpp
** File description:
** Abstract class for Entity interface
*/

#ifndef AENTITY_HPP_
	#define AENTITY_HPP_

#include "IEntity.hpp"

namespace arc
{
	class AEntity : public IEntity
	{
	public:
		AEntity(const std::string &name);
		const std::string &getName() const override;
		void setName(const std::string &name) override;
		int getHealth() const override;
		void setHealth(const int &health) override;
		int getAnimationStatus() const override;
		void setAnimationStatus(const int &animation) override;
		posf_t getPos() const override;
		void setPos(const posf_t &pos) override;
		Direction getDirection() const override;
		void setDirection(const Direction &direction) override;
		Direction getNextDirection() const override;
		void setNextDirection(const Direction &direction) override;

	protected:
		std::string _name;
		int _health;
		int _animationStatus;
		posf_t _pos;
		Direction _direction;
		Direction _nextDirection;
	};
}

arc::Direction getOppositeDir(const arc::Direction &dir);

#endif /* !AENTITY_HPP_ */
