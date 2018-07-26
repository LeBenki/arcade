/*
** EPITECH PROJECT, 2018
** LibCacaMenu.hpp
** File description:
** LibCacaMenu header file
*/

#ifndef LIBCACAMENU_HPP_
	#define LIBCACAMENU_HPP_

#include <caca.h>
#include <string>
#include <string.h>
#include <vector>
#include "IMenu.hpp"
#include "IEntity.hpp"
#include "EditTextLibCaca.hpp"

namespace arc
{
	class LibCacaMenu
	{
	public:
		LibCacaMenu(IMenu *menu, caca_canvas_t *canvas,
			    caca_display_t *window);
		void display(const int &width, const int &height) const;
		void drawMenuBorders(const int &width, const int &height)
		const;
		void drawSelection(const std::vector<std::string> &list,
				   const pos_t &offStart,
				   const pos_t &offEnd,
				   const int &selected) const;
		void processEvents(caca_event_t *event);
		void drawScores() const;

	private:
		IMenu *_menu;
		caca_canvas_t *_canvas;
		caca_display_t *_window;
		EditTextLibcaca _text;
	};
}
#endif /* !LIBCACAMENU_HPP_ */
