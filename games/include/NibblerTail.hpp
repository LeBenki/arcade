/*
** EPITECH PROJECT, 2018
** NibblerTail.hpp
** File description:
** NibblerTail class file
*/

#ifndef NIBBLERTAIL_HPP_
	#define NIBBLERTAIL_HPP_

#include "ANibbler.hpp"

namespace arc
{
	class NibblerTail : public ANibbler
	{
	public:
		NibblerTail(const int &x, const int &y);
		void giggle() override;
	};
}

#endif /* !NIBBLERTAIL_HPP_ */
