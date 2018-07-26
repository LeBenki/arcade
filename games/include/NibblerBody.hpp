/*
** EPITECH PROJECT, 2018
** NibblerBody.hpp
** File description:
** NibblerBody class file
*/

#ifndef NIBBLERBODY_HPP_
	#define NIBBLERBODY_HPP_

#include "ANibbler.hpp"

namespace arc
{
	class NibblerBody : public ANibbler
	{
	public:
		NibblerBody(const int &x, const int &y);
		void giggle() override;
	};
}

#endif /* !NIBBLERBODY_HPP_ */
