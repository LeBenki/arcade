/*
** EPITECH PROJECT, 2018
** SDLJoystick
** File description:
** Implementation of SDLJoystick
*/

#include "SDLJoystick.hpp"

arc::SDLJoystick::SDLJoystick() : joystick(nullptr)
{
}

void arc::SDLJoystick::stop()
{
	if (joystick)
		SDL_JoystickClose(joystick);
}

void arc::SDLJoystick::update(SDL_Event &event, std::vector<arc::IGame::Event> &events)
{
	if (!joystick)
		return;
	switch(event.jbutton.button)
	{
		case 0:
			events.push_back(arc::IGame::Event::ENTER);
			break;
		case 1:
			events.push_back(arc::IGame::Event::RESET);
			break;
		case 2:
			events.push_back(arc::IGame::Event::MENU);
			break;
		case 3:
			events.push_back(arc::IGame::Event::JUMP);
			break;
		default:
			break;
	}
}

void arc::SDLJoystick::init()
{
	SDL_JoystickEventState(SDL_ENABLE);
	if (SDL_NumJoysticks() >= 1)
		joystick = SDL_JoystickOpen(0);
}

void arc::SDLJoystick::updateAxe(SDL_Event &event,
				 std::vector<arc::IGame::Event> &events)
{
	if(event.jaxis.axis == 0 && event.jaxis.value < -14000)
		events.push_back(arc::IGame::Event::LEFT);
	else if (event.jaxis.axis == 0 && event.jaxis.value > 14000)
		events.push_back(arc::IGame::Event::RIGHT);
	else if(event.jaxis.axis == 1 && event.jaxis.value < -14000)
		events.push_back(arc::IGame::Event::UP);
	else if (event.jaxis.axis == 1 && event.jaxis.value > 14000)
		events.push_back(arc::IGame::Event::DOWN);
}
