/*
** EPITECH PROJECT, 2018
** ListViewSDL
** File description:
** Declaration of ListViewSDL
*/

#ifndef NANOTEKSPICE_LISTVIEWSDL_HPP
#define NANOTEKSPICE_LISTVIEWSDL_HPP


#include <SDL2/SDL_render.h>
#include <vector>
#include <string>
#include "TextureManager.hpp"
#include "IMenu.hpp"

namespace arc
{
	class ListViewSDL
	{
	public:
		ListViewSDL(const std::vector<std::string> &, SDL_Color,
			    SDL_Color, int, SDL_Renderer *);
		void update(SDL_Renderer *, int, int, int);
		virtual ~ListViewSDL();
	private:
		std::vector<SDL_Texture *> menuTextures;
		std::vector<SDL_Texture *> menuSelected;
		SDL_Rect menuRect;
		std::vector<std::string> strings;
	};
}

#endif //NANOTEKSPICE_LISTVIEWSDL_HPP
