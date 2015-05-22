#ifndef SHIP_H
#define SHIP_H
#include "flyingobject.h"
class View;
class Ship : public FlyingObject
{
public:
	Ship(View* view);
	virtual ~Ship();
	void init();
	void setX(float _x);
private:
	float width;
};

#endif // SHIP_H
