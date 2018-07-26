/*
** EPITECH PROJECT, 2018
** arc::EditTextLibcaca.cpp
** File description:
** EditText class for libcaca display module
*/

#include "EditTextLibCaca.hpp"

arc::EditTextLibcaca::EditTextLibcaca()
{
}

const std::string &arc::EditTextLibcaca::getUsername() const
{
	return _username;
}

void arc::EditTextLibcaca::setUsername(const std::string &username)
{
	_username = username;
}

void arc::EditTextLibcaca::addLetter(const char &c)
{
	_username.push_back(c);
}

void arc::EditTextLibcaca::removeLetter()
{
	if (_username.size() > 0)
		_username = _username.substr(0, _username.size() - 1);
}