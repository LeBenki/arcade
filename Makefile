##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

CXXFLAGS += -Iinclude/ -Igames/include/ -Ilib/include/
CXXFLAGS += -W -Wextra -Wall -Werror -std=c++14 -fpic -g3

NAME = arcade

SRCS =  src/main.cpp \
		src/Arcade.cpp	\
		src/AMenu.cpp	\
		src/ScoreManager.cpp \
		src/ArcadeExceptions.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -ldl
	make -C lib/
	make -C games/

core: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -ldl

games:
	make -C games/

graphicals:
	make -C lib/

clean:
	$(RM) $(OBJS)
	make clean -C lib/
	make clean -C games/

fclean: clean
	$(RM) $(NAME)
	make fclean -C lib/
	make fclean -C games/

re: fclean all
	make re -C lib/
	make re -C games/

.PHONY: all core games graphicals clean fclean re
