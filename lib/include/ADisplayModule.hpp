/*
** EPITECH PROJECT, 2018
** ADisplayModule
** File description:
** Declaration of ADisplayModule
*/

#ifndef ADisplayModule_HPP
	#define ADisplayModule_HPP

#include <iostream>
#include <string>
#include <memory>
#include "IDisplayModule.hpp"

namespace arc
{
	class ADisplayModule : public IDisplayModule
	{
	public:
		explicit ADisplayModule(const std::string &);
		const std::string &getName() const override;
		const std::string &getLibraryName() const override;
		void init() override = 0;
		void stop() override = 0;
		void display() override = 0;
		virtual void createWindow() = 0;
		State getState() const override;
		void setState(State) override;
		void setMenu(IMenu *) override;
		void setGame(IGame *) override;
		IGame *getGame() const override;
		IMenu *getMenu() const override;
		const std::vector<IGame::Event> &getEvents() override = 0;
	protected:
		std::string _name;
		std::string _libraryname;
		State _state;
		IMenu *_menu;
		IGame *_game;
		std::vector<arc::IGame::Event> events;
	};
}
#endif /* ADisplayModule_HPP */
