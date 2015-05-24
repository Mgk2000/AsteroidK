#ifndef BULLET_H
#define BULLET_H
#include "flyingobject.h"

class View;

class Bullet : public FlyingObject
{
public:
	Bullet(View* view, float _x, float _y, float _angle);
	virtual ~Bullet();
	void init();
	void draw();
	Point top() const;
	bool out() const;
private:

};

#endif // BULLET_H
