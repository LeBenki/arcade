/*
** EPITECH PROJECT, 2018
** OpenGLMenu
** File description:
** Declaration of OpenGLMenu
*/

#ifndef NANOTEKSPICE_OpenGLMenu_HPP
	#define NANOTEKSPICE_OpenGLMenu_HPP

#include <ctime>
#include <string>
#include <GL/glut.h>
#include <SDL/SDL_events.h>
#include <IMenu.hpp>
#include "OpenGLObject.hpp"

namespace arc
{
	class OpenGLMenu
	{
	public:
		explicit OpenGLMenu(IMenu *menu);
		void init();
		void display();
		void handleEvents(SDL_Event &event);
		void displayText(int x, int y, const std::string &s,
				 unsigned char r, unsigned char g,
				 unsigned char b);
		void addCharacter(SDLKey param);
		void removeCharacter();
	private:
		IMenu *_menu;
		std::string username;
		std::map<SDLKey, char> keys;
	};
}

#endif //NANOTEKSPICE_OpenGLMenu_HPP
