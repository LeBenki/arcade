/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#ifndef IDISPLAYMODULE_HPP
	#define IDISPLAYMODULE_HPP

#include <string>
#include <vector>
#include "IGame.hpp"
#include "IEntity.hpp"
#include "IMenu.hpp"

namespace arc
{
	class IDisplayModule
	{
	public:
		enum State
		{
			MENU,
			GAME
		};
		virtual ~IDisplayModule() = default;
		virtual const std::string &getName() const = 0;
		virtual const std::string &getLibraryName() const = 0;
		virtual void init() = 0;
		virtual void stop() = 0;
		virtual void display() = 0;
		virtual State getState() const = 0;
		virtual void setState(State) = 0;
		virtual void setMenu(IMenu *) = 0;
		virtual IMenu *getMenu() const = 0;
		virtual void setGame(IGame *) = 0;
		virtual IGame *getGame() const = 0;
		virtual const std::vector<arc::IGame::Event> &getEvents() = 0;
	};
}

#endif /*IDISPLAYMODULE_HPP*/