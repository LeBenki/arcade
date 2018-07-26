/*
** EPITECH PROJECT, 2018
** EditTextSDL
** File description:
** Declaration of EditTextSDL
*/

#ifndef NANOTEKSPICE_EDITTEXTSDL_HPP
	#define NANOTEKSPICE_EDITTEXTSDL_HPP

#include <SDL2/SDL_render.h>
#include <string>
#include <ctime>
#include <vector>
#include "TextureManager.hpp"

namespace arc
{
	class EditTextSDL
	{
	public:
		explicit EditTextSDL(SDL_Renderer *renderer,
				SDL_Color titleColor1,
				SDL_Color titleColor2,
				SDL_Color usernameColor,
				const std::string &username);
		const std::string &getUsername() const;
		void setUsername(const std::string &username);
		void update(int x, int y, bool blink);
		void addLetter(char c);
		void removeLetter();
		virtual ~EditTextSDL();
	private:
		SDL_Renderer *renderer;
		SDL_Texture *usernameTexture;
		std::vector<SDL_Texture *> titleTexture;
		std::string username;
		SDL_Color usernameColor;
		SDL_Rect titleRect;
		SDL_Rect userRect;
	};
}
#endif //NANOTEKSPICE_EDITTEXTSDL_HPP
