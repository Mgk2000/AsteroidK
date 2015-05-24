#ifndef ASTEROID_H
#define ASTEROID_H
#include "flyingobject.h"
class View;
class Asteroid : public FlyingObject
{
public:
	Asteroid(View * _view);
	virtual ~Asteroid();
	void init();
	void draw();
};

#endif // ASTEROID_H
