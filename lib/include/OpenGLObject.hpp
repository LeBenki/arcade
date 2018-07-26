/*
** EPITECH PROJECT, 2018
** OpenGLObject
** File description:
** Declaration of OpenGLObject
*/

#ifndef NANOTEKSPICE_OPENGLOBJECT_HPP
	#define NANOTEKSPICE_OPENGLOBJECT_HPP

#include <GL/gl.h>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "IEntity.hpp"
#include "OpenGLImage.hpp"

namespace arc
{
	class OpenGLPos
	{
	public:
		GLdouble x;
		GLdouble y;
		GLdouble z;
	};

	class OpenGLFace
	{
	public:
		GLint v1;
		GLint vt1;
		GLint vn1;
		GLint v2;
		GLint vt2;
		GLint vn2;
		GLint v3;
		GLint vt3;
		GLint vn3;
	};

	class OpenGLObject
	{
	public:
		explicit OpenGLObject(const std::string &filename);
		void display(double x, double y, double z, bool isEntity, arc::Direction direction = arc::DIR_UP);
		void displayFaceWithColor(OpenGLPos pos,
					OpenGLPos n, int i);
		void displayFaceWithTexture(OpenGLPos pos,
					OpenGLPos n, int i);
	private:
		std::vector<OpenGLPos> vertices;
		std::vector<OpenGLPos> normals;
		std::vector<OpenGLPos> textures;
		std::vector<OpenGLFace> faces;
		GLuint texture;
	};
}

#endif //NANOTEKSPICE_OPENGLOBJECT_HPP
