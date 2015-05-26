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
	const QVector4D&  color() const;
private:
//	bool isPointInside( Point* p) const;
	float width;
	float height;
	bool _dead;
	QVector4D alivecolor, deadcolor;

};

#endif // SHIP_H
