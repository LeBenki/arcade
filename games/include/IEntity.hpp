/*
** EPITECH PROJECT, 2018
** IEntity.hpp
** File description:
** IEntity class header file
*/

#ifndef IENTITY_HPP_
	#define IENTITY_HPP_

#include <iostream>

namespace arc
{
	typedef struct s_posf
	{
		float x;
		float y;
	} posf_t;

	typedef struct s_pos
	{
		int x;
		int y;
	} pos_t;

	enum Direction
	{
		DIR_UNDEFINED,
		DIR_UP,
		DIR_RIGHT,
		DIR_DOWN,
		DIR_LEFT
	};

	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual const std::string &getName() const = 0;
		virtual void setName(const std::string &name) = 0;
		virtual int getHealth() const = 0;
		virtual void setHealth(const int &health) = 0;
		virtual int getAnimationStatus() const = 0;
		virtual void setAnimationStatus(const int &animation) = 0;
		virtual posf_t getPos() const = 0;
		virtual void setPos(const posf_t &pos) = 0;
		virtual Direction getDirection() const = 0;
		virtual void setDirection(const Direction &direction) = 0;
		virtual Direction getNextDirection() const = 0;
		virtual void setNextDirection(const Direction &direction) = 0;
	};
}

#endif /* !IENTITY_HPP_ */
