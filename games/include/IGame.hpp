/*
** EPITECH PROJECT, 2018
** IGame.hpp
** File description:
** Game interface header file
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

#include <iostream>
#include <vector>
#include <sys/timeb.h>
#include <math.h>
#include "IEntity.hpp"

#define DIST(a, b) sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y))
#define ABS(x) ((x < 0) ? (-x) : (x))

namespace arc
{
	class IGame
	{
	public:
		enum Event
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			JUMP,
			ENTER,
			RETURN,
			NEXTGAME,
			PREVGAME,
			NEXTLIB,
			PREVLIB,
			PAUSE,
			EXIT,
			RESET,
			MENU
		};
		virtual ~IGame() = default;
		virtual void init() = 0;
		virtual const std::string &getName() const = 0;
		virtual void setName(const std::string &name) = 0;
		virtual const std::vector<std::string> &getMap() const = 0;
		virtual void setMap(const std::vector<std::string> &map) = 0;
		virtual long getScore() const = 0;
		virtual void setScore(long score) = 0;
		virtual std::vector<arc::IEntity *> &getEntities() = 0;
		virtual void
		setEntities(const std::vector<IEntity *> &entities) = 0;
		virtual bool update(const std::vector<Event> &events) = 0;
	};
}

#endif /* !IGAME_HPP_ */