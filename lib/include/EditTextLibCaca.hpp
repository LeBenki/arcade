/*
** EPITECH PROJECT, 2018
** EditTextLibCaca.hpp
** File description:
** Text edit class on libCaca display module
*/

#ifndef EDITTEXTLIBCACA_HPP_
	#define EDITTEXTLIBCACA_HPP_

#include <caca.h>
#include <string>
#include <ctime>
#include <vector>

namespace arc
{
	class EditTextLibcaca
	{
	public:
		EditTextLibcaca();
		const std::string &getUsername() const;
		void setUsername(const std::string &username);
		void addLetter(const char &c);
		void removeLetter();
	private:
		std::string _username;
	};
}

#endif /* !EDITTEXTLIBCACA_HPP_ */
