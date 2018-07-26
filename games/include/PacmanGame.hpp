/*
** EPITECH PROJECT, 2018
** PacmanGame.hpp
** File description:
** PacmanGame game header file
*/

#ifndef PACMANGAME_HPP_
	#define PACMANGAME_HPP_

#include <fstream>
#include <unistd.h>
#include "AGame.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "ArcadeExceptions.hpp"

#define MAP_PATH "res/pacman/maps/"
#define BUFFTIME 5

namespace arc
{
	class PacmanGame : public AGame
	{
	public:
		PacmanGame(const std::string &mapPath = "default.map");
		~PacmanGame();
		void init() override;
		void loadMap(const std::string &path = "default.map") override;
		void validMapCheck();
		bool update(const std::vector<Event> &events) override;
		void updatePlayer();
		void goalCheck();
		void interact();
		void killPlayer();
		void attack();
		void updateEnemies();
		void randomPath(IEntity &entity);
		void moveEnemy(IEntity &entity);
		void checkPlayerRotation();
		posf_t getNextTile(const posf_t &pos, const Direction &dir);
		bool isTileAccessible(const IEntity &entity,
					const posf_t &posFrom,
					const Direction &dir,
					const float &speed);
		void processMovements(std::vector<Event> events);
		std::vector<arc::IEntity *> &getEntities() override;
		void initEntities(const std::string &line, const int &y);
		void setAbsolutePos(posf_t &pos);

	private:
		std::vector<APacmanEntity *> _pacmanEntities;
		std::vector<IEntity *> ret;
		unsigned int _level;
		unsigned int _enemies;
		long _liveTime;
		long _buff;
		bool _gameover;
	};
}

extern "C" arc::IGame *getInstance();

#endif /* !PACMANGAME_HPP_ */
