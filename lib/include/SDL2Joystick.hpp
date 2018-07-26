/*
** EPITECH PROJECT, 2018
** SDLJoystick
** File description:
** Declaration of SDLJoystick
*/

#ifndef NANOTEKSPICE_SDLJOYSTICK_HPP
	#define NANOTEKSPICE_SDLJOYSTICK_HPP


#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_events.h>
#include <IGame.hpp>

namespace arc
{
	class SDL2Joystick
	{
	public:
		SDL2Joystick();
		void init();
		void stop();
		void update(SDL_Event &event, std::vector<arc::IGame::Event> &events);
		void updateAxe(SDL_Event &event, std::vector<arc::IGame::Event> &events);
	private:
		SDL_Joystick *joystick;
	};
}

#endif //NANOTEKSPICE_SDLJOYSTICK_HPP
