##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

CXXFLAGS 	+= 	-Iinclude/ -I../games/include/ -I../include/
CXXFLAGS 	+= 	-W -Wextra -Wall -Werror -std=c++14 -g3 -fPIC -Ofast

##LIBCACA##
NAME_CACA 	= 	lib_arcade_libcaca.so

SRCS_CACA 	=	src/ADisplayModule.cpp 	\
			src/LibCacaModule.cpp 	\
			src/EditTextLibcaca.cpp	\
			src/LibCacaMenu.cpp	\
			../src/ArcadeExceptions.cpp \

OBJS_CACA = $(SRCS_CACA:.cpp=.o)
###########


##OPENGL##
NAME_OPENGL 	= 	lib_arcade_opengl.so

SRCS_OPENGL 	=	src/ADisplayModule.cpp 	\
					src/LibOpenGL.cpp 	\
					src/OpenGLImage.cpp \
					src/ObjParser.cpp \
					src/OpenGLObject.cpp \
					src/OpenGLMenu.cpp \
					src/SDLJoystick.cpp \
					../src/ArcadeExceptions.cpp \

OBJS_OPENGL = $(SRCS_OPENGL:.cpp=.o)
###########

##LIBSDL##
NAME_SDL 	= 	lib_arcade_sdl2.so

SRCS_SDL 	=	src/ADisplayModule.cpp 	\
				src/LibSdlModule.cpp 	\
				src/TextureManager.cpp \
				src/ListViewSDL.cpp \
				src/EditTextSDL.cpp \
				src/SDL2Menu.cpp \
				src/SDL2Joystick.cpp \
				../src/ArcadeExceptions.cpp \

OBJS_SDL = $(SRCS_SDL:.cpp=.o)
##########

all: $(NAME_CACA) $(NAME_SDL) $(NAME_OPENGL)

$(NAME_CACA): $(OBJS_CACA)
	$(CC) $(OBJS_CACA) -shared -o $(NAME_CACA) -lcaca

$(NAME_OPENGL): $(OBJS_OPENGL)
	$(CC) $(OBJS_OPENGL) -shared -o $(NAME_OPENGL) -lSDL -lSDL_image -lGLU -lglut -lGL

$(NAME_SDL): $(OBJS_SDL)
	$(CC) $(OBJS_SDL) -shared -o $(NAME_SDL) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

clean:
	$(RM) $(OBJS_CACA)
	$(RM) $(OBJS_SDL)
	$(RM) $(OBJS_OPENGL)

fclean: clean
	$(RM) $(NAME_CACA)
	$(RM) $(NAME_SDL)
	$(RM) $(OBJS_OPENGL)

re: fclean all

.PHONY: all clean fclean re
