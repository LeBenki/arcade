/*
** EPITECH PROJECT, 2018
** LibOpenGL
** File description:
** Declaration of LibOpenGL
*/

#ifndef NANOTEKSPICE_LIBOPENGL_HPP
	#define NANOTEKSPICE_LIBOPENGL_HPP

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <map>
#include "ArcadeExceptions.hpp"
#include "ADisplayModule.hpp"
#include "OpenGLObject.hpp"
#include "OpenGLMenu.hpp"
#include "SDLJoystick.hpp"

namespace arc
{
	class LibOpenGL : public ADisplayModule
	{
	public:
		LibOpenGL();
		~LibOpenGL() override;
		void init() override;
		void stop() override;
		void display() override;
		void createWindow() override;
		void initMap();
		void initEntities();
		const std::vector<arc::IGame::Event> &getEvents() override;
		void moveCamera(SDLKey);
		void displayMap();
		void displayEntities();
		void displayText(int x, int y, const std::string &s);
	private:
		SDL_Event event;
		GLint cameraPos[3];
		std::map<std::string, OpenGLObject *> objects;
		std::map<char, OpenGLObject *> mapObjects;
		OpenGLMenu *menu;
		std::map<SDLKey, IGame::Event> eventsMap;
		SDLJoystick joystick;
	};
}
extern "C" arc::IDisplayModule *getInstance();

#endif //NANOTEKSPICE_LIBOPENGL_HPP
