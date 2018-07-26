/*
** EPITECH PROJECT, 2018
** ArcadeExceptions
** File description:
** Implementation of ArcadeExceptions
*/

#include "ArcadeExceptions.hpp"

arc::ArcadeExceptions::ArcadeExceptions(std::string const &message,
			std::string const &component) : std::exception()
{
	this->type = component;
	this->msg = this->type + ": " + message;
}

const char *arc::ArcadeExceptions::what() const throw()
{
	return this->msg.c_str();
}

arc::LibraryUnknown::LibraryUnknown(std::string const &msg) : arc::ArcadeExceptions(msg, "LibraryUnknown")
{

}

arc::InvalidMap::InvalidMap(std::string const &msg) : arc::ArcadeExceptions(msg, "InvalidMap")
{

}

arc::ResourceNotFound::ResourceNotFound(std::string const &msg) : arc::ArcadeExceptions(msg, "ResourceNotFound")
{

}

arc::InitError::InitError(std::string const &msg) : arc::ArcadeExceptions(msg, "InitError")
{

}
