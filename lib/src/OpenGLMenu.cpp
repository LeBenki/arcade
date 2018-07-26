/*
** EPITECH PROJECT, 2018
** arc::OpenGLMenu
** File description:
** Implementation of arc::OpenGLMenu
*/

#include "OpenGLMenu.hpp"

arc::OpenGLMenu::OpenGLMenu(IMenu *menu) : _menu(menu), username(menu->getName())
{
	keys = {{SDLK_a, 'a'} ,{SDLK_b, 'b'}, {SDLK_c, 'c'}, {SDLK_d, 'd'}, {SDLK_e, 'e'},
		{SDLK_f, 'f'}, {SDLK_g, 'g'}, {SDLK_h, 'h'}, {SDLK_i, 'i'}
		, {SDLK_j, 'j'}, {SDLK_k, 'k'}, {SDLK_l, 'l'}, {SDLK_m, 'm'}
		, {SDLK_n, 'n'}, {SDLK_o, 'o'}, {SDLK_p, 'p'}, {SDLK_q, 'q'}
		, {SDLK_r, 'r'}, {SDLK_s, 's'}, {SDLK_t, 't'}, {SDLK_u, 'u'}
		, {SDLK_v, 'v'}, {SDLK_w, 'w'}, {SDLK_x, 'x'}, {SDLK_y, 'y'}, {SDLK_z, 'z'}};
}

void arc::OpenGLMenu::init()
{
}

void arc::OpenGLMenu::display()
{
	int i = 0;
	int selected = 0;

	for (const std::string &string : _menu->getGames())
	{
		if (_menu->getGamesIdx() == selected)
			displayText(i, 0 - 30, string, 255, 0, 0);
		else
			displayText(i, 0 - 30, string, 255, 20, 147);
		i += 5;
		selected++;
	}
	i = 0;
	selected = 0;
	for (const std::string &string : _menu->getLibs())
	{
		if (_menu->getLibIdx() == selected)
			displayText(i, 0, string, 255, 0, 0);
		else
			displayText(i, 0, string, 255, 20, 147);
		i += 5;
		selected++;
	}
	i = 0;
	auto map = _menu->getScores();
	for (const std::string &string : map[_menu->getGames()[_menu->getGamesIdx()]])
	{
		if (0 == i)
			displayText(i, 30, string, 255, 215, 0);
		else
			displayText(i, 30, string, 210, 180, 140);
		i += 5;
	}
	displayText(0 - 50, 0 - 30, "Enter your name : " + username, 255, 0, 0);
}

void arc::OpenGLMenu::addCharacter(SDLKey key)
{
	if (keys.count(key))
	{
		username.push_back(keys[key]);
		_menu->setName(username);
	}
}

void arc::OpenGLMenu::handleEvents(SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			addCharacter(event.key.keysym.sym);
			switch (event.key.keysym.sym)
			{
				case SDLK_BACKSPACE:
					removeCharacter();
					_menu->setName(username);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void arc::OpenGLMenu::displayText(int x, int y, const std::string &s, unsigned char r, unsigned char g, unsigned char b)
{
	glColor3ub(r, g, b);
	glRasterPos2f(x, y);
	for(size_t i = 0; i < s.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
	glColor3d(1, 1, 1);
}

void arc::OpenGLMenu::removeCharacter()
{
	username = username.substr(0, username.size() - 1);
}
