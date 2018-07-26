##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

CXXFLAGS += -Iinclude/ -I../include/
CXXFLAGS += -W -Wextra -Wall -Werror -std=c++14 -g3 -fPIC

PACMAN_NAME = lib_arcade_pacman.so

NIBBLER_NAME = lib_arcade_nibbler.so

SOLARFOX_NAME = lib_arcade_solarfox.so

PACMAN_SRCS =	src/PacmanGame.cpp	\
		src/AEntity.cpp		\
		src/AGame.cpp		\
		src/APacmanEntity.cpp	\
		src/Pacman.cpp		\
		src/Ghost.cpp		\
		../src/ArcadeExceptions.cpp \

NIBBLER_SRCS = 	src/NibblerGame.cpp		\
		src/AEntity.cpp			\
		src/AGame.cpp			\
		src/ANibbler.cpp		\
		src/NibblerHead.cpp		\
		src/NibblerBody.cpp		\
		src/NibblerTail.cpp		\
		../src/ArcadeExceptions.cpp	\

SOLARFOX_SRCS	=	src/SolarFoxGame.cpp		\
			src/AEntity.cpp			\
			src/AGame.cpp			\
			src/ASolarFoxEntity.cpp		\
			src/Spaceship.cpp		\
			src/Sentinel.cpp		\
			src/Missile.cpp			\
			src/Laser.cpp			\
			../src/ArcadeExceptions.cpp	\

PACMAN_OBJS = $(PACMAN_SRCS:.cpp=.o)

NIBBLER_OBJS = $(NIBBLER_SRCS:.cpp=.o)

SOLARFOX_OBJS = $(SOLARFOX_SRCS:.cpp=.o)

all: $(PACMAN_NAME) $(NIBBLER_NAME) $(SOLARFOX_NAME)

$(PACMAN_NAME): $(PACMAN_OBJS)
	$(CC) $(PACMAN_OBJS) -shared -o $(PACMAN_NAME)

$(NIBBLER_NAME): $(NIBBLER_OBJS)
	$(CC) $(NIBBLER_OBJS) -shared -o $(NIBBLER_NAME)

$(SOLARFOX_NAME): $(SOLARFOX_OBJS)
	$(CC) $(SOLARFOX_OBJS) -shared -o $(SOLARFOX_NAME)

clean:
	$(RM) $(PACMAN_OBJS) $(NIBBLER_OBJS) $(SOLARFOX_OBJS)

fclean: clean
	$(RM) $(PACMAN_NAME) $(NIBBLER_NAME) $(SOLARFOX_OBJS)

re: fclean all

.PHONY: all clean fclean re
