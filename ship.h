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
	virtual void getCurrentCoords (Point * vertices, int* nvertices ) const;
	virtual void moveStep();

	void die();
	void revive();
	bool dead() {return _dead;}
	const Point4D&  color() const;
	void draw();
private:
//	bool isPointInside( Point* p) const;
	float width;
	float height;
	bool _dead;
	Point4D alivecolor, deadcolor;

};

#endif // SHIP_H
