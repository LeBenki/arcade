/*
** EPITECH PROJECT, 2018
** LibCacaModule.cpp
** File description:
** LibCacaModule class file
*/

#include "LibCacaModule.hpp"

arc::LibCacaModule::LibCacaModule() : ADisplayModule::ADisplayModule("LibCaca"),
_libcacaMenu(nullptr, nullptr, nullptr)
{
	_libraryname = "lib_arcade_libcaca.so";
	memset(&_event, 0, sizeof(caca_event_t));
	eventsMap = {{CACA_KEY_F1, IGame::PREVLIB},
		{CACA_KEY_F2, IGame::NEXTLIB}, {CACA_KEY_F3, IGame::PREVGAME},
		{CACA_KEY_F4, IGame::NEXTGAME}, {CACA_KEY_LEFT, IGame::LEFT},
		{CACA_KEY_RIGHT, IGame::RIGHT}, {' ', IGame::JUMP},
		{CACA_KEY_RETURN, IGame::ENTER}, {CACA_KEY_UP, IGame::UP},
		{CACA_KEY_DOWN, IGame::DOWN}, {CACA_KEY_ESCAPE, IGame::EXIT},
		{CACA_KEY_DELETE, IGame::RETURN}, {'r', IGame::RESET},
		{'m', IGame::MENU}
	};
	_colors = {
		{"BLUE", CACA_BLUE}, {"GREEN", CACA_GREEN},
		{"CYAN", CACA_CYAN}, {"RED", CACA_RED},
		{"MAGENTA", CACA_MAGENTA}, {"BROWN", CACA_BROWN},
		{"LIGHTGRAY", CACA_LIGHTGRAY}, {"DARKGRAY", CACA_DARKGRAY},
		{"LIGHTBLUE", CACA_LIGHTBLUE}, {"LIGHTGREEN", CACA_LIGHTGREEN},
		{"LIGHTCYAN", CACA_LIGHTCYAN}, {"LIGHTRED", CACA_LIGHTRED},
		{"LIGHTMAGENTA", CACA_LIGHTMAGENTA}, {"YELLOW", CACA_YELLOW},
		{"WHITE", CACA_WHITE},
	};
}

arc::LibCacaModule::~LibCacaModule()
{
}

void arc::LibCacaModule::init()
{
	_width = 120;
	_height = 40;
	_cursor = 0;
	createWindow();
	_libcacaMenu = LibCacaMenu(_menu, _canvas, _window);
}

void arc::LibCacaModule::stop()
{
	destroyWindow();
}

void arc::LibCacaModule::createWindow()
{
	_canvas = caca_create_canvas(_width, _height);
	_window = caca_create_display(_canvas);
	caca_set_display_title(_window, GAMETITLE);
}

void arc::LibCacaModule::destroyWindow()
{
	caca_free_display(_window);
	caca_free_canvas(_canvas);
}

void arc::LibCacaModule::displayHUD()
{
	posf_t mapSize = {(float)_game->getMap().size(),
			(float)_game->getMap()[0].size()};
	int health = _game->getEntities()[0]->getHealth();

	caca_printf(_canvas, _width / 2 - mapSize.x - 10, mapSize.y / 2,
					"Score:%d\n", _game->getScore());
	caca_printf(_canvas, _width / 2 - mapSize.x - 10, mapSize.y / 2 + 1,
					"Lives:%d\n", health);
}

void arc::LibCacaModule::displayMap()
{
	std::vector<std::string> map = _game->getMap();
	pos_t topleft = {_width / 2 - (int)map[0].size(),
			_height / 2 - (int)map.size() / 2};

	loadMapTextures();
	for (unsigned int i = 0; i < map.size(); i++) {
		for (unsigned int j = 0; j < map[i].size(); j++) {
			if (_tiles.count(map[i][j]))
				caca_set_color_ansi(_canvas,
						_colors[_tiles[map[i][j]]],
						CACA_BLACK);
			else
				caca_set_color_ansi(_canvas, CACA_WHITE,
								CACA_BLACK);
			caca_printf(_canvas, topleft.x + j * 2,
					topleft.y + i, "%c", map[i][j]);
		}
	}
	caca_set_color_ansi(_canvas, CACA_LIGHTGRAY, CACA_BLACK);
}

void arc::LibCacaModule::loadEntities()
{
	std::vector<std::string> cache;
	std::string value;

	for (IEntity *entity : _game->getEntities()) {
		if (_entities.count(entity->getName()))
			continue;
		std::ifstream stream(RES_PATH + _game->getName() + "/"
					+ entity->getName() + ".ascii");
		while (getline(stream, value))
			_entities[entity->getName()].push_back(value);
		if (_entities[entity->getName()].size() != 2
			|| _entities[entity->getName()][0].size() != 5
			|| _colors.count(_entities[entity->getName()][1]) == 0)
		{
			_entities[entity->getName()].clear();
			_entities[entity->getName()].push_back("?????");
			_entities[entity->getName()].push_back("WHITE");
		}
	}
}

void arc::LibCacaModule::loadMapTextures()
{
	std::vector<std::string> cache;
	std::string value;

	for (const std::string &line : _game->getMap())
		for (const char c : line)
			if (!_tiles.count(c)) {
				std::ifstream stream(RES_PATH
					+ _game->getName() + "/"
					+ c + ".ascii");
				getline(stream, value);
				if (!_colors.count(value))
					_tiles[c] = "WHITE";
				else
					_tiles[c] = value;
			}
}

void arc::LibCacaModule::displayEntities()
{
	std::vector<IEntity *> entities = _game->getEntities();
	std::vector<std::string> map = _game->getMap();
	pos_t topleft = {_width / 2 - (int)map[0].size(),
			_height / 2 - (int)map.size() / 2};
	pos_t pos;

	loadEntities();
	for (unsigned int i = 0; i < entities.size(); i++) {
		pos = {(int)entities[i]->getPos().x,
			(int)entities[i]->getPos().y};
		caca_set_color_ansi(_canvas, _colors[_entities[entities[i]
						->getName()][1]], CACA_BLACK);
		caca_printf(_canvas, topleft.x + pos.x * 2,
				topleft.y + pos.y, "%c",
				_entities[entities[i]->getName()][0]
					[entities[i]->getDirection()]);
	}
	caca_set_color_ansi(_canvas, CACA_LIGHTGRAY, CACA_BLACK);
}

void arc::LibCacaModule::display()
{
	caca_get_event(_window, CACA_EVENT_KEY_PRESS, &_event, 100);

	if (_state == IDisplayModule::MENU) {
		_libcacaMenu.processEvents(&_event);
		_libcacaMenu.display(_width, _height);
	}
	else
	{
		caca_clear_canvas(_canvas);
		displayMap();
		displayHUD();
		displayEntities();
		caca_refresh_display(_window);
	}
}

const std::vector<arc::IGame::Event> &arc::LibCacaModule::getEvents()
{
	events.clear();
	if (caca_get_event_type(&_event) != CACA_EVENT_KEY_PRESS)
		return events;
	events.push_back(eventsMap[caca_get_event_key_ch(&_event)]);
	return (events);
}

extern "C" arc::IDisplayModule *getInstance()
{
	return new arc::LibCacaModule();
}