/*
** EPITECH PROJECT, 2018
** arc::SDL2Menu
** File description:
** Implementation of arc::SDL2Menu
*/

#include "SDL2Menu.hpp"

arc::SDL2Menu::SDL2Menu(IMenu *menu, SDL_Renderer *renderer) : games(), libs(),
							menuRect(), renderer(renderer),
							editText(), _menu(menu),
							background()
{
}

void arc::SDL2Menu::init()
{
	background = TextureManager::LoadTexture("res/arcade.jpg",
						renderer);
	games = new ListViewSDL(_menu->getGames(),
				(SDL_Color) {255, 20, 147, 255},
				(SDL_Color) {255, 0, 0, 255},
				24,
				renderer);
	libs = new ListViewSDL(_menu->getLibs(),
				(SDL_Color) {255, 20, 147, 255},
				(SDL_Color) {255, 0, 0, 255},
				24,
				renderer);
	editText = new EditTextSDL(renderer,
				(SDL_Color) {255, 0, 0, 255},
				(SDL_Color) {0, 255, 0, 255},
				(SDL_Color) {0, 255, 0, 255}, _menu->getName());
	const std::map<std::string, std::vector<std::string>> &mapScores = _menu->getScores();
	auto &map = const_cast<std::map<std::string, std::vector<std::string>> &>(mapScores);
	for (std::pair<const std::string, std::vector<std::string>> &i : map)
		scores[i.first] = new ListViewSDL(i.second,
					(SDL_Color) {210, 180, 140, 255},
					(SDL_Color) {255, 215, 0, 255},
					24,
					renderer);
	SDL_StartTextInput();
}

void arc::SDL2Menu::display()
{
	SDL_RenderCopy(renderer, background, nullptr, nullptr);
	games->update(renderer, 300, 250, _menu->getGamesIdx());
	libs->update(renderer, 700, 250, _menu->getLibIdx());
	scores[_menu->getGames()[_menu->getGamesIdx()]]->update(renderer, 1100, 250, 0);
	editText->update(300, 275, _menu->getState() == IMenu::PLAYER);
}

void arc::SDL2Menu::handleEvents(SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_BACKSPACE:
					editText->removeLetter();
					_menu->setName(
						editText->getUsername());
					break;
				default:
					break;
			}
			break;
		case SDL_TEXTINPUT:
			if (_menu->getState() == 2)
			{
				editText->addLetter(event.text.text[0]);
				_menu->setName(editText->getUsername());
			}
			break;
		default:
			break;
	}
}
arc::SDL2Menu::~SDL2Menu()
{
	for (auto &i : scores)
		delete i.second;
	delete games;
	delete libs;
	delete editText;
	SDL_DestroyTexture(background);
}
