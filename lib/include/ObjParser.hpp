/*
** EPITECH PROJECT, 2018
** ObjParser
** File description:
** Declaration of ObjParser
*/

#ifndef NANOTEKSPICE_OBJPARSER_HPP
	#define NANOTEKSPICE_OBJPARSER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "OpenGLObject.hpp"

namespace arc
{
	class ObjParser
	{
	public:
		explicit ObjParser(const std::string &filename);
		void parse();
		void
		parseFace(const std::string &line, OpenGLFace *face, int n);
		void addFace(std::string &str);
		void addVertice(std::string &str, int i, std::vector<OpenGLPos> &vec);
		const std::vector<OpenGLPos> &getVertices() const;
		const std::vector<OpenGLPos> &getNormals() const;
		const std::vector<OpenGLFace> &getFaces() const;
		const std::vector<OpenGLPos> &getTextures() const;
	private:
		std::string filename;
		std::vector<OpenGLPos> vertices;
		std::vector<OpenGLPos> normals;
		std::vector<OpenGLFace> faces;
		std::vector<OpenGLPos> textures;
	};
}

#endif //NANOTEKSPICE_OBJPARSER_HPP
