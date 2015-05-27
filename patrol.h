#ifndef PATROL_H
#define PATROL_H
#include "flyingobject.h"

class View;
class Random;
class Patrol : public FlyingObject
{
public:
	Patrol(View* _view);
	virtual ~Patrol();
	void init();
	void draw();
//	bool isPointInside( Point* p) const;
	bool out() const;
	void moveStep();
//	virtual bool isSplinter() {return false;}
	float R() const {return r;}
	void getCurrentCoords (Point * vertices, int* nvertices ) const;
private:
	float width;

};

#endif // PATROL_H
