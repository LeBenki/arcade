/*
** EPITECH PROJECT, 2018
** arc::EditTextSDL
** File description:
** Implementation of arc::EditTextSDL
*/

#include "EditTextSDL.hpp"

arc::EditTextSDL::EditTextSDL(SDL_Renderer *renderer,
			SDL_Color titleColor1,
			SDL_Color titleColor2,
			SDL_Color usernameColor,
			const std::string &username)
		: renderer(renderer),
		username(username), usernameColor(usernameColor)
{
	titleTexture.push_back(TextureManager::LoadTextTexture(
		"res/monospace.ttf", "Enter your name :", 24, titleColor1,
		renderer));
	titleTexture.push_back(TextureManager::LoadTextTexture(
		"res/monospace.ttf", "Enter your name :", 24, titleColor2,
		renderer));
	usernameTexture = TextureManager::LoadTextTexture(
		"res/monospace.ttf", this->username, 24, usernameColor,
		renderer);
}

arc::EditTextSDL::~EditTextSDL()
{
	for (auto &i : titleTexture)
		SDL_DestroyTexture(i);
	SDL_DestroyTexture(usernameTexture);
}

const std::string &arc::EditTextSDL::getUsername() const
{
	return username;
}

void arc::EditTextSDL::setUsername(const std::string &username)
{
	EditTextSDL::username = username;
}

void arc::EditTextSDL::update(int x, int y, bool blink)
{
	titleRect.w = 24 * 17;
	titleRect.h = 24 * 2;
	titleRect.x = x;
	titleRect.y = y;
	userRect.w = username.size() * 24;
	userRect.h = 24 * 2;
	userRect.x = x + titleRect.w + 24;
	userRect.y = y;
	SDL_RenderCopy(renderer, usernameTexture, nullptr, &userRect);
	if (blink)
		SDL_RenderCopy(renderer, titleTexture[std::time(0) % 2], nullptr, &titleRect);
	else
		SDL_RenderCopy(renderer, titleTexture[0], nullptr, &titleRect);
}

void arc::EditTextSDL::addLetter(char c)
{
	username.push_back(c);
	usernameTexture = TextureManager::LoadTextTexture(
		"res/monospace.ttf", username, 24, usernameColor,
		renderer);
}

void arc::EditTextSDL::removeLetter()
{
	username = username.substr(0, username.size() - 1);
	usernameTexture = TextureManager::LoadTextTexture(
		"res/monospace.ttf", username, 24, usernameColor,
		renderer);
}
