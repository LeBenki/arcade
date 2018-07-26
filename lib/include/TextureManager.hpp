/*
** EPITECH PROJECT, 2018
** TextureManager
** File description:
** Declaration of TextureManager
*/

#ifndef NANOTEKSPICE_TEXTUREMANAGER_HPP
	#define NANOTEKSPICE_TEXTUREMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "IEntity.hpp"

#define SPRITES_LINES 4
#define SPRITES_COLS 3

namespace arc
{
	class TextureManager
	{
	public:
		static SDL_Texture *
		LoadTexture(const char *filename, SDL_Renderer *ren);
		static SDL_Texture *LoadTextTexture(const char *filename,
						const std::string &font,
						int size, SDL_Color color,
						SDL_Renderer *ren);
		static void drawEntity(const IEntity *entity, SDL_Rect mapCase,
				SDL_Renderer *renderer,
				SDL_Texture *texture, double mapSizeX, double mapSizeY);
	};
}

#endif //NANOTEKSPICE_TEXTUREMANAGER_HPP
