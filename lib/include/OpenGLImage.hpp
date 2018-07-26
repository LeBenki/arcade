/*
** EPITECH PROJECT, 2018
** OpenGLImage
** File description:
** Declaration of OpenGLImage
*/

#ifndef NANOTEKSPICE_OPENGLIMAGE_HPP
	#define NANOTEKSPICE_OPENGLIMAGE_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace arc
{
	class OpenGLImage
	{
	public:
		static GLuint loadImage(const std::string &);
	};
}

#endif //NANOTEKSPICE_OPENGLIMAGE_HPP
