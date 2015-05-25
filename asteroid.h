#ifndef ASTEROID_H
#define ASTEROID_H
#include "flyingobject.h"
class View;
class Random;
class Asteroid : public FlyingObject
{
public:
	Asteroid(View * _view, Random* _random);
	virtual ~Asteroid();
	void init();
	void initParams();
	void applyParams();
	void draw();
	bool isPointInside( Point* p) const;
	bool out() const;
	void moveStep();
	virtual bool isSplinter() {return false;}
	float R() const {return r;}
protected:
	Point* rotatedVertices;
	double rotateAngle;
	float r;
	Random* random;
};

class Splinter : public Asteroid
{
public:
	Splinter (View* view, Random* _random);
	virtual ~Splinter();
	void init(const Asteroid &parent, float fi);
	bool isSplinter() {return true;}
};

#endif // ASTEROID_H
