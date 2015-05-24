#include "ship.h"
#include "view.h"

Ship::Ship(View* _view): FlyingObject(_view)
{
	init();
}

Ship::~Ship()
{

}

void Ship::init()
{
	//FlyingObject::init();
	x =0.f;
	y=-0.5f;
	angle = 0.f;
	rotateSpeed = 0.0f;
	width = 0.2;
	height = width * 1.5;
	vertices = new Point[6];
	vertices[0] = Point (-width /2 , 0, 0);
	vertices[1] = Point (width /2, 0, 0);
	vertices[2] = Point (0 , height, 0);

	vertices[3] = Point (-width /4, 0, 0);
	vertices[4] = Point (0, -width/4, 0);
	vertices[5] = Point (width /4, 0, 0);
	nvertices = 6;

	indices = new GLushort [6];
	for (int i = 0; i< 6; i++)
		indices[i] = i;
	nindices = 6;
	fill_vbos();
	color = QVector4D(0.0, 0.7, 0.0, 1.0);
}

void Ship::setX(float _x)
{
	x=_x;
}

bool Ship::touched(float _x, float _y) const
{
	const float delta = 0.15;
	float dx = _x-x;
	if (dx > delta || dx < -delta)
		return false;
	float dy = y-_y;
	if (dy > delta || dy < -delta)
		return false;
	return true;
}

float Ship::top() const
{
	return y + height;
}
