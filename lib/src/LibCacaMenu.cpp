/*
** EPITECH PROJECT, 2018
** arc::LibCacaMenu.cpp
** File description:
** arc::LibCacaMenu class implementation
*/

#include "LibCacaMenu.hpp"

arc::LibCacaMenu::LibCacaMenu(IMenu *menu, caca_canvas_t *canvas,
					caca_display_t *window)
{
	_menu = menu;
	_canvas = canvas;
	_window = window;
}

void arc::LibCacaMenu::drawMenuBorders(const int &width, const int &height) const
{
	caca_draw_line(_canvas, 1, 1, width - 2, 1, '-');
	caca_draw_line(_canvas, 1, height - 2, width - 2, height - 2, '-');
	caca_draw_line(_canvas, 1, 1, 1, height - 2, '|');
	caca_draw_line(_canvas, width - 2, 1, width - 2, height - 2, '|');
	caca_printf(_canvas, 1, 1, "%c", '+');
	caca_printf(_canvas, width - 2, 1, "%c", '+');
	caca_printf(_canvas, 1, height - 2, "%c", '+');
	caca_printf(_canvas, width - 2, height - 2, "%c", '+');
}

void arc::LibCacaMenu::drawSelection(const std::vector<std::string> &list,
					const pos_t &offStart,
					const pos_t &offEnd,
					const int &selected) const
{
	if (list.size() == 0)
		return;
	int spaceLength = (offEnd.y - offStart.y) / list.size();
	for (unsigned int i = 0; i < list.size(); i++) {
		if ((int)i == selected)
			caca_set_color_ansi(_canvas, CACA_WHITE, CACA_CYAN);
		else if (selected < 0 && i == abs(selected + 1))
			caca_set_color_ansi(_canvas, CACA_YELLOW,
							CACA_DARKGRAY);
		caca_printf(_canvas, offStart.x, offStart.y + i * spaceLength,
						"%s\n", list[i].data());
		caca_set_color_ansi(_canvas, CACA_WHITE, CACA_DARKGRAY);
	}
}

void arc::LibCacaMenu::processEvents(caca_event_t *event)
{
	char key;

	if (_menu->getState() != IMenu::State::PLAYER)
		return;
	if (caca_get_event_type(event) == CACA_EVENT_KEY_PRESS) {
		key = caca_get_event_key_ch(event);
		switch (key) {
			case CACA_KEY_BACKSPACE:
				_text.removeLetter();
				_menu->setName(_text.getUsername());
				break;
			default:
				if (isprint(key)) {
					_text.addLetter(key);
					_menu->setName(_text.getUsername());
				}
				break;
		}
	}
}

void arc::LibCacaMenu::drawScores() const
{
	std::map<std::string, std::vector<std::string>> scores = _menu
								->getScores();

	caca_printf(_canvas, 70, 10, "%s highscores:",
			_menu->getGames()[_menu->getGamesIdx()].data());
	this->drawSelection(scores[_menu->getGames()[_menu->getGamesIdx()]],
				{70, 15}, {70, 35}, -1);
}

void arc::LibCacaMenu::display(const int &width, const int &height) const
{
	std::map<std::string, std::vector<std::string>> scores;

	caca_clear_canvas(_canvas);
	this->drawMenuBorders(width, height);
	caca_printf(_canvas, width / 2 - strlen(GAMETITLE) / 2, 2, "%s\n",
							GAMETITLE);
	caca_printf(_canvas, 10, 10, "Games:");
	this->drawSelection(_menu->getGames(), {10, 15}, {20, 35},
							_menu->getGamesIdx());
	caca_printf(_canvas, 30, 10, "Display:");
	this->drawSelection(_menu->getLibs(), {30, 15}, {30, 35},
							_menu->getLibIdx());
	this->drawScores();
	if (time(NULL) % 2 == 0 && _menu->getState()
		== arc::IMenu::State::PLAYER)
		caca_set_color_ansi(_canvas, CACA_CYAN, CACA_RED);
	caca_printf(_canvas, 5, 5, "Enter your name: %s",
						_menu->getName().data());
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_DARKGRAY);
	caca_refresh_display(_window);
}