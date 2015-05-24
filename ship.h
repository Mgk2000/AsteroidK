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
	bool touched(float _x, float _y) const;
	float top() const;
private:
	float width;
	float height;
};

#endif // SHIP_H
