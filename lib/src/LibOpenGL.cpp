/*
** EPITECH PROJECT, 2018
** LibSFMLWithOpenGL
** File description:
** Implementation of LibSFMLWithOpenGL
*/

#include "LibOpenGL.hpp"

arc::LibOpenGL::LibOpenGL() : ADisplayModule("LibOpenGL")
{
	_libraryname = "lib_arcade_opengl.so";
	eventsMap = {{SDLK_F1, IGame::PREVLIB},
		{SDLK_F2, IGame::NEXTLIB},
		{SDLK_F3, IGame::PREVGAME},
		{SDLK_F4, IGame::NEXTGAME},
		{SDLK_LEFT, IGame::LEFT},
		{SDLK_RIGHT, IGame::RIGHT},
		{SDLK_SPACE, IGame::JUMP},
		{SDLK_RETURN, IGame::ENTER},
		{SDLK_UP, IGame::UP},
		{SDLK_DOWN, IGame::DOWN},
		{SDLK_ESCAPE, IGame::EXIT},
		{SDLK_DELETE, IGame::RETURN},
		{SDLK_r, IGame::RESET},
		{SDLK_m, IGame::MENU}
	};
}

arc::LibOpenGL::~LibOpenGL()
{
}

void arc::LibOpenGL::init()
{
	createWindow();
	cameraPos[0] = 30;
	cameraPos[1] = 0;
	cameraPos[2] = 50;
	if (_state == GAME)
	{
		initEntities();
		initMap();
	}
	else
	{
		menu = new OpenGLMenu(_menu);
		menu->init();
	}
	joystick.init();
}

void arc::LibOpenGL::stop()
{
	joystick.stop();
	if (_state == GAME)
	{
		for (auto &mapObject : mapObjects)
			delete mapObject.second;
		for (auto &entityObject : objects)
			delete entityObject.second;
		mapObjects.clear();
		objects.clear();
	}
	SDL_Quit();
}

void arc::LibOpenGL::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0,
		0, 1);
	if (_state == GAME)
	{
		displayMap();
		displayEntities();
	}
	else
	{
		menu->display();
	}
	glFlush();
	SDL_GL_SwapBuffers();
}

void arc::LibOpenGL::createWindow()
{
	static bool initglut = false;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw arc::InitError("OPENGL init");
	atexit(SDL_Quit);
	SDL_WM_SetCaption("SDL GL Application", nullptr);
	SDL_SetVideoMode(1600, 900, 32, SDL_OPENGL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,(double)1600 / 900, 1, 1000);
	glEnable(GL_DEPTH_TEST);
	if (!initglut)
	{
		int ac = 1;
		char const *av[ac] = {
			"./arcade"
		};
		glutInit(&ac, const_cast<char **>(av));
		initglut = true;
	}
}

void arc::LibOpenGL::initMap()
{
	for (unsigned int i = 0; i < _game->getMap().size(); ++i)
	{
		for (unsigned int j = 0; j < _game->getMap()[i].size(); ++j)
		{
			if (!mapObjects.count(_game->getMap()[i][j]))
				mapObjects[_game->getMap()[i][j]] =
					new OpenGLObject(
						"res/" + _game->getName()
						+ "/" + _game->getMap()[i][j] +
						".obj");
		}
	}
}

void arc::LibOpenGL::initEntities()
{
	for (const auto &i : _game->getEntities())
		if (!objects.count(i->getName()))
			objects[i->getName()] = new OpenGLObject("res/"
				+ _game->getName() + "/" + i->getName() + ".obj");
}

const std::vector<arc::IGame::Event> &arc::LibOpenGL::getEvents()
{
	events.clear();
	while (SDL_PollEvent(&event))
	{
		if (_state == IDisplayModule::MENU)
			menu->handleEvents(event);
		switch (event.type)
		{
			case SDL_JOYAXISMOTION:
				joystick.updateAxe(event, events);
				break;
			case SDL_JOYBUTTONDOWN:
				joystick.update(event, events);
				break;
			case SDL_KEYDOWN:
				if (eventsMap.count(event.key.keysym.sym))
					events.push_back(eventsMap[event.key.keysym.sym]);
				moveCamera(event.key.keysym.sym);
				break;
			case SDL_QUIT:
				events.push_back(IGame::Event::EXIT);
				break;
			default:
				break;
		}
	}
	return events;
}

void arc::LibOpenGL::displayMap()
{
	for (unsigned int i = 0; i < _game->getMap().size(); ++i)
	{
		for (unsigned int j = 0; j < _game->getMap()[i].size(); ++j)
		{
			if (!mapObjects.count(_game->getMap()[i][j]))
				mapObjects[_game->getMap()[i][j]] =
				new OpenGLObject("res/" + _game->getName()
				+ "/" + _game->getMap()[i][j] + ".obj");
			else
				mapObjects[_game->getMap()[i][j]]->
					display((GLint)((i - _game->getMap().size() / 2) * 2),
						 (GLint)((j - _game->getMap()[i].size() / 2) * 2),
						 (GLint)0, false);
		}
	}
}

void arc::LibOpenGL::displayText(int x, int y, const std::string &s)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f(x, y);
	for(size_t i = 0; i < s.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
	glColor3d(1, 1, 1);
}

static arc::posf_t calcRotatedEntityPos(const arc::IEntity *entity, float x, float y)
{
	arc::Direction direction = entity->getDirection();
	direction = ((direction == arc::DIR_UP) ? arc::DIR_DOWN :
		     (direction == arc::DIR_DOWN) ? arc::DIR_UP : direction);
	double rad = 90 * direction * M_PI / 180;
	arc::posf_t buff;
	arc::posf_t ret;
	arc::posf_t pos = entity->getPos();
	arc::posf_t mapsize = (arc::posf_t){y / 2, x / 2};

	buff.x = pos.x - mapsize.x;
	buff.y = pos.y - mapsize.y;
	ret.x = buff.x * cos(rad) - buff.y * sin(rad) + mapsize.x;
	ret.y = buff.x * sin(rad) + buff.y * cos(rad) + mapsize.y;
	return ret;
}

void arc::LibOpenGL::displayEntities()
{
	posf_t pos;
	int count = 0;
	displayText(-50, -50, std::string("Score : "
			+ std::to_string(_game->getScore())));
	displayText(-40, -50, std::string("Lives : "
			+ std::to_string(_game->getEntities()[0]->getHealth())));
	for (const IEntity *i : _game->getEntities())
	{
		pos = calcRotatedEntityPos(i, _game->getMap().size(), _game->getMap()[0].size());
		if (objects.count(i->getName()))
			objects[i->getName()]->display(((pos.y - 0.5) - _game->getMap().size() / 2) * 2,
				 ((pos.x - 0.5) - _game->getMap()[0].size() / 2) * 2,
				 0, true, i->getDirection());
		else
			objects[i->getName()] = new OpenGLObject("res/"
				+ _game->getName() + "/" + i->getName() + ".obj");
		++count;
	}
}
void arc::LibOpenGL::moveCamera(SDLKey)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_PAGEUP:
			cameraPos[2] += 1;
			break;
		case SDLK_PAGEDOWN:
			cameraPos[2] -= 1;
			break;
		case SDLK_z:
			cameraPos[0] += 1;
			break;
		case SDLK_s:
			cameraPos[0] -= 1;
			break;
		case SDLK_q:
			cameraPos[1] += 1;
			break;
		case SDLK_d:
			cameraPos[1] -= 1;
			break;
		default:
			break;
	}
}

extern "C" arc::IDisplayModule *getInstance()
{
	return new arc::LibOpenGL();
}