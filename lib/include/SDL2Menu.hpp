/*
** EPITECH PROJECT, 2018
** SDL2Menu
** File description:
** Declaration of SDL2Menu
*/

#ifndef NANOTEKSPICE_SDL2MENU_HPP
	#define NANOTEKSPICE_SDL2MENU_HPP

#include <ctime>
#include "EditTextSDL.hpp"
#include "ListViewSDL.hpp"

namespace arc
{
	class SDL2Menu
	{
	public:
		explicit SDL2Menu(IMenu *menu, SDL_Renderer *renderer);
		virtual ~SDL2Menu();
		void init();
		void display();
		void handleEvents(SDL_Event &event);
	private:
		ListViewSDL *games;
		ListViewSDL *libs;
		std::map<std::string, ListViewSDL *> scores;
		SDL_Rect menuRect;
		SDL_Renderer *renderer;
		EditTextSDL *editText;
		IMenu *_menu;
		SDL_Texture *background;
	};
}

#endif //NANOTEKSPICE_SDL2MENU_HPP
