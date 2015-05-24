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
	void setColor(float r , float g , float b) {color = QVector4D (r,g,b,1.0);}
	bool isPointInside( Point* p) const;
	bool out() const;

};

#endif // ASTEROID_H
