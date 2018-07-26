/*
** EPITECH PROJECT, 2018
** ArcadeExceptions
** File description:
** Declaration of ArcadeExceptions
*/

#ifndef NANOTEKSPICE_ARCADEEXCEPTIONS_HPP
	#define NANOTEKSPICE_ARCADEEXCEPTIONS_HPP

#include <exception>
#include <string>

namespace arc
{
	class ArcadeExceptions : public std::exception
	{
	public:
		explicit ArcadeExceptions(std::string const &msg, std::string const &type = "Unknown");
		const char *what() const throw() final;
	private:
		std::string msg;
		std::string type;
	};
	class LibraryUnknown : public ArcadeExceptions
	{
	public:
		explicit LibraryUnknown(std::string const &);
	};
	class InvalidMap : public ArcadeExceptions
	{
	public:
		explicit InvalidMap(std::string const &);
	};
	class ResourceNotFound : public ArcadeExceptions
	{
	public:
		explicit ResourceNotFound(std::string const &);
	};
	class InitError : public ArcadeExceptions
	{
	public:
		explicit InitError(std::string const &);
	};
}

#endif //NANOTEKSPICE_ARCADEEXCEPTIONS_HPP
