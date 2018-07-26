/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <Arcade.hpp>

int main(int ac, const char **av)
{
	arc::Arcade *arcade = nullptr;

	if (ac == 2)
	{
		arcade = new arc::Arcade(std::string(av[1]));
		arcade->gameLoop();
		delete arcade;
	}
	else
	{
		std::cerr << "Arcade takes only 1 argument" << std::endl;
		return (84);
	}
}
