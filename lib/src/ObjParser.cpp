/*
** EPITECH PROJECT, 2018
** arc::ObjParser
** File description:
** Implementation of arc::ObjParser
*/

#include "ObjParser.hpp"

arc::ObjParser::ObjParser(const std::string &filename) : filename(filename)
{

}

static bool BothAreSpaces(char lhs, char rhs)
{
	return (lhs == rhs) && (std::isspace(lhs));
}

void arc::ObjParser::parse()
{
	std::ifstream in(filename.c_str());

	std::string str;
	while (std::getline(in, str))
	{
		std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
		str.erase(new_end, str.end());
		if (str[0] == 'v' && str[1] == ' ')
			addVertice(str, 2, vertices);
		else if (str[0] == 'v' && str[1] == 'n')
			addVertice(str, 3, normals);
		else if (str[0] == 'v' && str[1] == 't')
			addVertice(str, 3, textures);
		else if (str[0] == 'f' && str[1] == ' ')
			addFace(str);
	}
}

const std::vector<arc::OpenGLPos> &arc::ObjParser::getVertices() const
{
	return vertices;
}

const std::vector<arc::OpenGLPos> &arc::ObjParser::getNormals() const
{
	return normals;
}

const std::vector<arc::OpenGLFace> &arc::ObjParser::getFaces() const
{
	return faces;
}

static std::string doubleSlash(std::string s)
{
	std::string s1 = "";

	for(unsigned int i=0;i<s.size();i++)
	{
		if( i < s.size() - 1 && s[i]== '/' && s[i + 1] == '/')
		{
			s1 += "/1/";
			i++;
		}
		else
			s1 += s[i];
	}
	return s1;
}

void arc::ObjParser::parseFace(const std::string &line, OpenGLFace *face, int n)
{
	std::string s1;
	std::string s2;
	std::string s3;
	std::istringstream os(doubleSlash(line));

	getline(os, s1, '/');
	getline(os, s2, '/');
	getline(os, s3, '\0');
	switch (n)
	{
		case 1:
			face->v1 = atoi(s1.c_str());
			face->vt1 = atoi(s2.c_str());
			face->vn1 = atoi(s3.c_str());
			break;
		case 2:
			face->v2 = atoi(s1.c_str());
			face->vt2 = atoi(s2.c_str());
			face->vn2 = atoi(s3.c_str());
			break;
		case 3:
			face->v3 = atoi(s1.c_str());
			face->vt3 = atoi(s2.c_str());
			face->vn3 = atoi(s3.c_str());
			break;
		default:
			break;
	}
}
const std::vector<arc::OpenGLPos> &arc::ObjParser::getTextures() const
{
	return textures;
}
void arc::ObjParser::addVertice(std::string &str, int i, std::vector<OpenGLPos> &vec)
{
	OpenGLPos openGLPos;

	str = str.substr(i, str.size() - 1);
	std::istringstream os(str);
	os >> openGLPos.x;
	os >> openGLPos.y;
	os >> openGLPos.z;
	vec.push_back(openGLPos);
}
void arc::ObjParser::addFace(std::string &str)
{
	str = str.substr(2, str.size() - 1);
	std::istringstream os(str);
	OpenGLFace openGLFace;
	getline(os, str, ' ');
	parseFace(str, &openGLFace, 1);
	getline(os, str, ' ');
	parseFace(str, &openGLFace, 2);
	getline(os, str, '\0');
	parseFace(str, &openGLFace, 3);
	faces.push_back(openGLFace);
}
