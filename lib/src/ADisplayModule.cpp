/*
** EPITECH PROJECT, 2018
** arc::ADisplayModule
** File description:
** Implementation of arc::ADisplayModule
*/

#include <iostream>
#include "ADisplayModule.hpp"

arc::ADisplayModule::ADisplayModule(std::string const &name) : _name(name)
{
}

const std::string &arc::ADisplayModule::getName() const
{
	return _name;
}

arc::IDisplayModule::State arc::ADisplayModule::getState() const
{
	return _state;
}

void arc::ADisplayModule::setState(IDisplayModule::State state)
{
	_state = state;
}

void arc::ADisplayModule::setMenu(IMenu *menu)
{
	_menu = menu;
}

void arc::ADisplayModule::setGame(IGame *game)
{
	_game = game;
}

arc::IGame *arc::ADisplayModule::getGame() const
{
	return _game;
}

arc::IMenu *arc::ADisplayModule::getMenu() const
{
	return _menu;
}

const std::string &arc::ADisplayModule::getLibraryName() const
{
	return _libraryname;
}
