/*
** EPITECH PROJECT, 2018
** arc::OpenGLObject
** File description:
** Implementation of arc::OpenGLObject
*/

#include "OpenGLObject.hpp"
#include "ObjParser.hpp"

arc::OpenGLObject::OpenGLObject(const std::string &filename)
{
	ObjParser objParser(filename);
	std::string texturePath;

	objParser.parse();
	vertices = objParser.getVertices();
	normals = objParser.getNormals();
	textures = objParser.getTextures();
	faces = objParser.getFaces();
	texturePath = filename.substr(0, filename.size() - 3);
	texturePath += "jpg";
	texture = arc::OpenGLImage::loadImage(texturePath);
}

void arc::OpenGLObject::displayFaceWithColor(
					OpenGLPos pos,
					OpenGLPos n, int i)
{
	glBegin(GL_TRIANGLES);
	glColor3ub(255 * pow(n.x, 2), 255 * pow(n.y, 2), 255 * pow(n.z, 2));
	glNormal3d(n.x, n.y, n.z);
	glVertex3d(vertices[faces[i].v1 - 1].x + pos.x,
		vertices[faces[i].v1 - 1].y + pos.y,
		vertices[faces[i].v1 - 1].z + pos.z);
	glVertex3d(vertices[faces[i].v2 - 1].x + pos.x,
		vertices[faces[i].v2 - 1].y + pos.y,
		vertices[faces[i].v2 - 1].z + pos.z);
	glVertex3d(vertices[faces[i].v3 - 1].x + pos.x,
		vertices[faces[i].v3 - 1].y + pos.y,
		vertices[faces[i].v3 - 1].z + pos.z);
	glColor3ub(255,255,255);
	glEnd();
}

void arc::OpenGLObject::displayFaceWithTexture(OpenGLPos pos, OpenGLPos n, int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glNormal3d(n.x, n.y, n.z);
	glTexCoord2d(textures[faces[i].vt1 - 1].x, textures[faces[i].vt1 - 1].y);
	glVertex3d(vertices[faces[i].v1 - 1].x + pos.x,
		vertices[faces[i].v1 - 1].y + pos.y,
		vertices[faces[i].v1 - 1].z + pos.z);
	glTexCoord2d(textures[faces[i].vt2 - 1].x, textures[faces[i].vt2 - 1].y);
	glVertex3d(vertices[faces[i].v2 - 1].x + pos.x,
		vertices[faces[i].v2 - 1].y + pos.y,
		vertices[faces[i].v2 - 1].z + pos.z);
	glTexCoord2d(textures[faces[i].vt3 - 1].x, textures[faces[i].vt3 - 1].y);
	glVertex3d(vertices[faces[i].v3 - 1].x + pos.x,
		vertices[faces[i].v3 - 1].y + pos.y,
		vertices[faces[i].v3 - 1].z + pos.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void arc::OpenGLObject::display(double x, double y, double z, bool isEntity, arc::Direction direction)
{
	OpenGLPos v = {0,0,0};
	OpenGLPos w = {0,0,0};
	OpenGLPos n = {0,0,0};
	GLdouble lenN;


	direction = ((direction == arc::DIR_UP) ? arc::DIR_DOWN :
		     ((direction == arc::DIR_DOWN) ? arc::DIR_UP : direction));
	for(unsigned int i = 0 ; i < faces.size(); ++i)
	{
		w.x = vertices[faces[i].v1 - 1].x - vertices[faces[i].v2 - 1].x;
		w.y = vertices[faces[i].v1 - 1].y - vertices[faces[i].v2 - 1].y;
		w.z = vertices[faces[i].v1 - 1].z - vertices[faces[i].v2 - 1].z;
		v.x = vertices[faces[i].v3 - 1].x - vertices[faces[i].v2 - 1].x;
		v.y = vertices[faces[i].v3 - 1].y - vertices[faces[i].v2 - 1].y;
		v.z = vertices[faces[i].v3 - 1].z - vertices[faces[i].v2 - 1].z;
		n.x = (v.y * w.z) - (v.z * w.y);
		n.y = (v.z * w.x) - (v.x * w.z);
		n.z = (v.x * w.y) - (v.y * w.x);
		lenN = sqrt((n.x*n.x) + (n.y*n.y) + (n.z*n.z));
		n.x = n.x / lenN;
		n.y = n.y / lenN;
		n.z = n.z / lenN;
		if (isEntity)
		{
			glPushMatrix();
			glRotatef(90 * direction, 0, 0, 1);
		}
		if (textures.size() == 0 || texture == 0)
			displayFaceWithColor({x, y, z}, n, i);
		else
			displayFaceWithTexture({x, y, z}, n , i);
		if (isEntity)
			glPopMatrix();
	}
}