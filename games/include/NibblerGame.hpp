/*
** EPITECH PROJECT, 2018
** NibblerGame.hpp
** File description:
** Nibbler game header file
*/

#ifndef NIBBLERGAME_HPP_
	#define NIBBLERGAME_HPP_

#include <fstream>
#include <chrono>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "AGame.hpp"
#include "ANibbler.hpp"
#include "NibblerHead.hpp"
#include "NibblerBody.hpp"
#include "NibblerTail.hpp"
#include "ArcadeExceptions.hpp"

#define MAP_PATH "res/nibbler/maps/"
#define MOVES_PER_SECTION 1 + (float)1 / NIBBLERSPEED

namespace arc
{
	class NibblerGame : public AGame
	{
	public:
		NibblerGame();
		void init() override;
		void loadMap(const std::string &path = "default.map") override;
		void validMapCheck();
		void initEntities(const std::string &line, const int &y);
		bool update(const std::vector<Event> &events) override;
		void processEvents(const std::vector<Event> &events);
		bool possibleMovement(const posf_t &pos, const Direction &dir,
				      const float &speed) const;
		posf_t getNextPos(const posf_t &pos, const Direction &dir,
				  const float &speed) const;
		void updateDirections();
		void movePlayer();
		void rotatePlayer();
		void interact();
		void growPlayer();
		void spawnFood();
		void stuckCheck();
		void clearMovements();
		std::vector<IEntity *> &getEntities()override;

	private:
		std::vector<ANibbler *> _player;
		std::vector<Direction> _movements;
		struct timeval _stuck;
		bool _gameover;
		std::vector<IEntity *> ret;
	};
}

extern "C" arc::IGame *getInstance();

#endif /* !NIBBLERGAME_HPP_ */
