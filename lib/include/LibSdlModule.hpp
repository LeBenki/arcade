/*
** EPITECH PROJECT, 2018
** LibSdlModule.hpp
** File description:
** SDL module header file
*/

#ifndef LIBSDLMODULE_HPP_
	#define LIBSDLMODULE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "ADisplayModule.hpp"
#include "TextureManager.hpp"
#include "ListViewSDL.hpp"
#include "EditTextSDL.hpp"
#include "SDL2Menu.hpp"
#include "ArcadeExceptions.hpp"
#include "SDL2Joystick.hpp"

namespace arc
{
	class LibSdlModule : public ADisplayModule
	{
	public:
		LibSdlModule();
		~LibSdlModule() override;
		void init() override;
		void stop() override;
		void display() override;
		void createWindow() override;
		void initMap();
		void initEntities();
		const std::vector<arc::IGame::Event> &getEvents() override;
		void displayMap();
		void displayEntities();
		void displayHUD();
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *background;
		SDL_Rect mapCase;
		std::map<char, SDL_Texture *> mapTextures;
		std::map<std::string, SDL_Texture *> entitiesTextures;
		SDL_Event event;
		SDL2Menu *menuSDL;
		SDL_Texture *score;
		SDL_Texture *lives;
		std::map<int, IGame::Event> eventsMap;
		SDL2Joystick joystick;
	};
}

extern "C" arc::IDisplayModule *getInstance();

#endif /* !LIBSDLMODULE_HPP_ */
