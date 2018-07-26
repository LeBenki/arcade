/*
** EPITECH PROJECT, 2018
** SolarFoxGame.hpp
** File description:
** SolarFox game class
*/

#ifndef SOLARFOXGAME_HPP_
	#define SOLARFOXGAME_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "AGame.hpp"
#include "ArcadeExceptions.hpp"
#include "ASolarFoxEntity.hpp"
#include "Spaceship.hpp"
#include "Sentinel.hpp"
#include "Missile.hpp"

#define MAP_PATH "res/solarfox/maps/"

namespace arc
{
	class SolarFoxGame : public AGame
	{
		public:
			SolarFoxGame();
			void init() override;
			void loadMap(const std::string &map = "default.map");
			void validMapCheck();
			bool update(const std::vector<Event> &events) override;
			void processEvents(const std::vector<Event> &events);
			void initEntities();
			void shipsMovement();
			void shipsRotation();
			void destroyProjectiles();
			std::vector<arc::IEntity *> &getEntities() override;
			void goalCheck();

		private:
			std::vector<ASolarFoxEntity *> _ships;
			std::vector<IEntity *> ret;
			unsigned int _level;
	};
}

extern "C" arc::IGame *getInstance();

#endif /* !SOLARFOXGAME_HPP_ */
