/*
** EPITECH PROJECT, 2018
** ANibbler.hpp
** File description:
** Nibbler abstract class file
*/

#ifndef ANIBBLER_HPP_
	#define ANIBBLER_HPP_

#include <math.h>
#include "AEntity.hpp"

#define NIBBLERSPEED 0.2

namespace arc
{
	class ANibbler : public AEntity
	{
	public:
		ANibbler(const std::string &name, const int &x, const int &y);
		virtual void giggle() = 0;
		virtual void move();
		int getMoves() const;
		void setMoves(const int &moves);
		void justifyPos();

	private:
		int _moves;
	};
}

#endif /* !ANIBBLER_HPP_ */
