/*
** EPITECH PROJECT, 2018
** LibCacaModule.hpp
** File description:
** LibCacaModule header file
*/

#ifndef LIBCACAMODULE_HPP_
	#define LIBCACAMODULE_HPP_

#include <caca.h>
#include <string.h>
#include <map>
#include <iostream>
#include <fstream>
#include "ADisplayModule.hpp"
#include "LibCacaMenu.hpp"

#define RES_PATH "res/"

namespace arc
{
	class LibCacaModule : public ADisplayModule
	{
	public:
		LibCacaModule();
		~LibCacaModule();
		void init() override;
		void stop() override;
		void createWindow() override;
		void destroyWindow();
		void loadEntities();
		void loadMapTextures();
		void display() override;
		void displayMap();
		void displayHUD();
		void displayEntities();
		const std::vector<arc::IGame::Event> &getEvents() override;

	private:
		caca_canvas_t *_canvas;
		caca_display_t *_window;
		caca_event_t _event;
		std::map<std::string, std::vector<std::string>> _entities;
		std::map<char, std::string> _tiles;
		int _cursor;
		int _width;
		int _height;
		LibCacaMenu _libcacaMenu;
		std::map<int, arc::IGame::Event> eventsMap;
		std::map<std::string, caca_color> _colors;
	};
}

extern "C" arc::IDisplayModule *getInstance();

#endif /* !LIBCACAMODULE_HPP_ */
