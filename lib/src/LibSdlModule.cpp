/*
** EPITECH PROJECT, 2018
** arc::LibSdlModule.cpp
** File description:
** SDL module class file
*/

#include "LibSdlModule.hpp"

arc::LibSdlModule::LibSdlModule() : ADisplayModule("LibSDL"), window(), renderer(),
			background(), score(nullptr), lives(nullptr)
{
	_libraryname = "lib_arcade_sdl2.so";
	eventsMap = {{SDLK_F1, IGame::PREVLIB},
		{SDLK_F2, IGame::NEXTLIB},
		{SDLK_F3, IGame::PREVGAME},
		{SDLK_F4, IGame::NEXTGAME},
		{SDLK_LEFT, IGame::LEFT},
		{SDLK_RIGHT, IGame::RIGHT},
		{SDLK_SPACE, IGame::JUMP},
		{SDLK_RETURN, IGame::ENTER},
		{SDLK_UP, IGame::UP},
		{SDLK_DOWN, IGame::DOWN},
		{SDLK_ESCAPE, IGame::EXIT},
		{SDLK_DELETE, IGame::RETURN},
		{SDLK_r, IGame::RESET},
		{SDLK_m, IGame::MENU}
	};
}

arc::LibSdlModule::~LibSdlModule() = default;

void arc::LibSdlModule::init()
{
	createWindow();
	TTF_Init();
	if (_state == IDisplayModule::MENU)
	{
		menuSDL = new SDL2Menu(_menu, renderer);
		menuSDL->init();
	}
	else if (_state == IDisplayModule::GAME)
	{
		initMap();
		initEntities();
		score = TextureManager::LoadTextTexture("res/monospace.ttf", "Score : "
				+ std::to_string(_game->getScore()),
							24, {255, 255, 255, 255}, renderer);
		lives = TextureManager::LoadTextTexture("res/monospace.ttf",
				"Lives : " + std::to_string(_game->getEntities()[0]->getHealth()),
				24, {255, 255, 255, 255}, renderer);
	}
	joystick.init();
}

void arc::LibSdlModule::stop()
{
	joystick.stop();
	if (_state == GAME)
	{
		for (auto &i : mapTextures)
			SDL_DestroyTexture(i.second);
		for (auto &i : entitiesTextures)
			SDL_DestroyTexture(i.second);
		mapTextures.clear();
		entitiesTextures.clear();
		SDL_DestroyTexture(lives);
		SDL_DestroyTexture(score);
	}
	else
	{
		delete menuSDL;
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_StopTextInput();
	TTF_Quit();
	SDL_Quit();
}

void arc::LibSdlModule::createWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw arc::InitError("SDL init");
	if (SDL_CreateWindowAndRenderer(1600, 900, 0, &window, &renderer))
		throw arc::InitError("SDL window or renderer");
}

void arc::LibSdlModule::display()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	if (_state == IDisplayModule::MENU)
	{
		menuSDL->display();
	}
	else if (_state == IDisplayModule::GAME)
	{
		SDL_RenderCopy(renderer, background, nullptr, nullptr);
		displayMap();
		displayEntities();
		displayHUD();
	}
	SDL_RenderPresent(renderer);
}

const std::vector<arc::IGame::Event> &arc::LibSdlModule::getEvents()
{
	events.clear();
	while (SDL_PollEvent(&event))
	{
		if (_state == IDisplayModule::MENU)
			menuSDL->handleEvents(event);
		switch (event.type)
		{
			case SDL_JOYAXISMOTION:
				joystick.updateAxe(event, events);
				break;
			case SDL_JOYBUTTONDOWN:
				joystick.update(event, events);
				break;
			case SDL_KEYDOWN:
				if (eventsMap.count(event.key.keysym.sym))
					events.push_back(eventsMap[event.key.keysym.sym]);
				break;
			case SDL_QUIT:
				events.push_back(IGame::Event::EXIT);
				break;
			default:
				break;
		}
	}
	return events;
}

void arc::LibSdlModule::displayMap()
{
	for (unsigned int i = 0; i < _game->getMap().size(); ++i)
		for (unsigned int j = 0; j < _game->getMap()[i].size(); ++j)
		{
			if (_game->getMap()[0].size() > _game->getMap().size())
			{
				mapCase.x = j * mapCase.w;
				mapCase.y = i * mapCase.h + (mapCase.h * _game->getMap().size() / 2);
			}
			else
			{
				mapCase.x = j * mapCase.w + (mapCase.w * _game->getMap()[i].size() / 2);
				mapCase.y = i * mapCase.h;
			}
			if (mapTextures.count(_game->getMap()[i][j]))
				SDL_RenderCopy(renderer,
					mapTextures[_game->getMap()[i][j]],
					nullptr, &mapCase);
			else
				mapTextures[_game->getMap()[i][j]] =
					TextureManager::LoadTexture(
					std::string("res/" + _game->getName()
					+ "/" + _game->getMap()[i][j] + ".png").c_str(),
					renderer);

		}
}

void arc::LibSdlModule::initMap()
{
	background = TextureManager::LoadTexture(std::string("res/"
		+ _game->getName() + "/background.png").c_str(),
						renderer);
	for (unsigned int i = 0; i < _game->getMap().size(); ++i)
	{
		for (unsigned int j = 0; j < _game->getMap()[i].size(); ++j)
		{
			if (!mapTextures.count(_game->getMap()[i][j]))
				mapTextures[_game->getMap()[i][j]] =
				TextureManager::LoadTexture(
					std::string("res/" + _game->getName()
					+ "/" + _game->getMap()[i][j] + ".png").c_str(),
						renderer);
		}
	}
	SDL_GetWindowSize(window, &mapCase.w, &mapCase.h);
	mapCase.w /= _game->getMap()[0].size();
	mapCase.h /= _game->getMap().size();
	if ((mapCase.w < mapCase.h))
		mapCase.h = mapCase.w;
	else
		mapCase.w = mapCase.h;
}

void arc::LibSdlModule::initEntities()
{
	for (const IEntity *entity : _game->getEntities())
		entitiesTextures[entity->getName()] =
			TextureManager::LoadTexture(std::string("res/"
			+ _game->getName() + "/" + entity->getName() + ".png").c_str(),
						renderer);
}

void arc::LibSdlModule::displayEntities()
{
	for (const IEntity *entity : _game->getEntities())
		if (entitiesTextures.count(entity->getName()))
			TextureManager::drawEntity(entity, mapCase, renderer,
			entitiesTextures[entity->getName()], _game->getMap()[0].size(), _game->getMap().size());
		else
			entitiesTextures[entity->getName()] =
				TextureManager::LoadTexture(std::string("res/"
				+ _game->getName() + "/" + entity->getName() + ".png").c_str(),
							renderer);
}

void arc::LibSdlModule::displayHUD()
{
	static int livesInt = 0;
	static int scoreInt = 0;
	SDL_Rect rect;

	rect.w = 24 * 11;
	rect.h = 50;
	rect.x = 0;
	rect.y = 0;
	if (scoreInt != _game->getScore())
	{
		scoreInt = _game->getScore();
		SDL_DestroyTexture(score);
		score = TextureManager::LoadTextTexture("res/monospace.ttf", "Score : "
				+ std::to_string(_game->getScore()),
				24, {255, 255, 255, 255}, renderer);
	}
	if (livesInt != _game->getEntities()[0]->getHealth())
	{
		livesInt = _game->getEntities()[0]->getHealth();
		SDL_DestroyTexture(lives);
		lives = TextureManager::LoadTextTexture("res/monospace.ttf",
							"Lives : "
			+ std::to_string(_game->getEntities()[0]->getHealth()),
			24, {255, 255, 255, 255}, renderer);
	}
	SDL_RenderCopy(renderer, score, nullptr, &rect);
	rect.y += 50;
	SDL_RenderCopy(renderer, lives, nullptr, &rect);
}

extern "C" arc::IDisplayModule *getInstance()
{
	return new arc::LibSdlModule();
}