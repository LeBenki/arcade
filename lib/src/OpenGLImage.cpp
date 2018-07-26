/*
** EPITECH PROJECT, 2018
** OpenGLImage
** File description:
** Implementation of OpenGLImage
*/

#include "OpenGLImage.hpp"

static inline SDL_Surface *flip(SDL_Surface *surface)
{
	int current_line,pitch;
	SDL_Surface *rgbSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
							surface->w,surface->h,
							surface->format->BitsPerPixel,
							surface->format->Rmask,
							surface->format->Gmask,
							surface->format->Bmask,
							surface->format->Amask);

	SDL_LockSurface(surface);
	SDL_LockSurface(rgbSurface);
	pitch = surface->pitch;
	for (current_line = 0; current_line < surface->h; current_line++)
	{
		memcpy(&((unsigned char* )rgbSurface->pixels)[current_line*pitch],
		&((unsigned char* )surface->pixels)[(surface->h - 1 -
							current_line)*pitch],
		pitch);
	}
	SDL_UnlockSurface(rgbSurface);
	SDL_UnlockSurface(surface);
	return rgbSurface;
}

GLuint arc::OpenGLImage::loadImage(const std::string &name)
{
	GLuint glID;
	SDL_Surface *picture_surface = nullptr;
	SDL_Surface *gl_surface = nullptr;
	SDL_Surface *flipedSurface = nullptr;
	Uint32 rmask, gmask, bmask, amask;

	picture_surface = IMG_Load(name.c_str());
	if (picture_surface == NULL)
		return 0;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	}
	else
	{
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
	SDL_PixelFormat format = *(picture_surface->format);
	format.BitsPerPixel = 32;
	format.BytesPerPixel = 4;
	format.Rmask = rmask;
	format.Gmask = gmask;
	format.Bmask = bmask;
	format.Amask = amask;
	gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);
	flipedSurface = flip(gl_surface);
	glGenTextures(1, &glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, flipedSurface->w,
			flipedSurface->h, GL_RGBA,GL_UNSIGNED_BYTE,
			flipedSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	SDL_FreeSurface(flipedSurface);
	SDL_FreeSurface(gl_surface);
	SDL_FreeSurface(picture_surface);
	return glID;
}
