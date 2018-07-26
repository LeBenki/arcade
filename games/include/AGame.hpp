/*
** EPITECH PROJECT, 2018
** AGame.hpp
** File description:
** Game abstract class header file
*/

#ifndef AGAME_HPP_
	#define AGAME_HPP_

#include "IGame.hpp"

namespace arc
{
	class AGame : public IGame
	{
	public:
		AGame(const std::string &name);
		virtual void
		loadMap(const std::string &path = "default.map") = 0;
		void init() override;
		const std::string &getName() const override;
		void setName(const std::string &name) override;
		const std::vector<std::string> &getMap() const override;
		void setMap(const std::vector<std::string> &map) override;
		long getScore() const override;
		void setScore(const long score) override;
		std::vector<IEntity *> &getEntities() override;
		void
		setEntities(const std::vector<IEntity *> &entities) override;
		virtual bool
		update(const std::vector<Event> &events) override = 0;
	protected:
		std::string _name;
		int _score;
		long _time;
		std::vector<IEntity *> _entities;
		std::vector<std::string> _map;
		std::vector<std::string> _cachedMap;
	};
}

#endif /* !IGAME_HPP_ */