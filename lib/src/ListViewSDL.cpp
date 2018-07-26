/*
** EPITECH PROJECT, 2018
** arc::ListViewSDL
** File description:
** Implementation of arc::ListViewSDL
*/

#include "ListViewSDL.hpp"

arc::ListViewSDL::ListViewSDL(const std::vector<std::string> &games,
			SDL_Color normal, SDL_Color selected, int size,
			SDL_Renderer *renderer) : strings(games)
{
	for (const std::string &name : games)
	{
		menuTextures.push_back(TextureManager::LoadTextTexture(
			"res/monospace.ttf", name, size, normal,
			renderer));
		menuSelected.push_back(TextureManager::LoadTextTexture(
			"res/monospace.ttf", name, size, selected,
			renderer));
	}

}

arc::ListViewSDL::~ListViewSDL()
{
	for (auto &i : menuTextures)
		SDL_DestroyTexture(i);
	for (auto &i : menuSelected)
		SDL_DestroyTexture(i);
	menuTextures.clear();
	menuSelected.clear();
	strings.clear();
}

void arc::ListViewSDL::update(SDL_Renderer *renderer, int x, int y, int idx)
{
	int i = 0;

	menuRect.h = 24 * 2;
	menuRect.x = x;
	menuRect.y = y;
	for (SDL_Texture *texture : menuTextures)
	{
		menuRect.w = strings[i].size() * 24;
		menuRect.y += 100;
		if (i == idx)
			SDL_RenderCopy(renderer, menuSelected[i], nullptr, &menuRect);
		else
			SDL_RenderCopy(renderer, texture, nullptr, &menuRect);
		++i;
	}
}

