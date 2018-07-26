/*
** EPITECH PROJECT, 2018
** TextureManager
** File description:
** Implementation of TextureManager
*/

#include "TextureManager.hpp"

SDL_Texture *arc::TextureManager::LoadTexture(const char *filename,
					SDL_Renderer *ren)
{
	SDL_Surface *tmpSurface = IMG_Load(filename);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tmpSurface);

	SDL_FreeSurface(tmpSurface);
	return texture;
}

SDL_Texture *
arc::TextureManager::LoadTextTexture(const char *filename, const std::string &font,
				int size, SDL_Color color, SDL_Renderer *ren)
{
	TTF_Font *monospace = TTF_OpenFont(filename, size);
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(monospace, font.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surfaceMessage);

	SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(monospace);
	return texture;
}

void arc::TextureManager::drawEntity(const IEntity *entity, SDL_Rect mapCase,
				SDL_Renderer *renderer,
				SDL_Texture *texture, double sizeMapX, double sizeMapY)
{
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	SDL_Rect sprite;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	switch (entity->getDirection())
	{
		case Direction::DIR_RIGHT:
			y = 1;
			break;
		case Direction::DIR_LEFT:
			y = 0;
			break;
		case Direction::DIR_UP:
			y = 2;
			break;
		case Direction::DIR_DOWN:
			y = 3;
			break;
		default:
			break;
	}
	x = entity->getAnimationStatus();
	sprite.w = w / SPRITES_COLS;
	sprite.h = h / SPRITES_LINES;
	sprite.x = x * (w / SPRITES_COLS);
	sprite.y = y * (h / SPRITES_LINES);
	if (sizeMapY >= sizeMapX)
	{
		mapCase.x = (entity->getPos().x) * mapCase.w - mapCase.w / 2 +
			    (mapCase.w * sizeMapX / 2);
		mapCase.y = (entity->getPos().y) * mapCase.h - mapCase.h / 2;
	}
	else
	{
		mapCase.x = (entity->getPos().x) * mapCase.w - mapCase.w / 2;
		mapCase.y = (entity->getPos().y) * mapCase.h - mapCase.h / 2 +
				(mapCase.h * sizeMapY / 2);
	}
	SDL_RenderCopy(renderer, texture, &sprite, &mapCase);
}
