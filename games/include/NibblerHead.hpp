/*
** EPITECH PROJECT, 2018
** NibblerHead.hpp
** File description:
** NibblerHead header file
*/

#ifndef NIBBLERHEAD_HPP_
	#define NIBBLERHEAD_HPP_

#include "ANibbler.hpp"

namespace arc
{
	class NibblerHead : public ANibbler
	{
	public:
		NibblerHead(const int &x, const int &y);
		void giggle() override;
	};
}

#endif /* !NIBBLERHEAD_HPP_ */
