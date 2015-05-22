#include "ship.h"
#include "Kmainwidget.h"

Ship::Ship(View* _view): FlyingObject(_view)
{
}

Ship::~Ship()
{

}

void Ship::init()
{
	FlyingObject::init();
	x =0.f;
	y=-1.f;
	angle = 0.f;
	width = 0.5;
	vertices = new QVector3D[6];
	vertices[0] = QVector3D (-width /2 , 0, 0);
	vertices[1] = QVector3D (width /2, 0, 0);
	vertices[2] = QVector3D (0 , width * 1.5, 0);

	vertices[3] = QVector3D (-width /4, 0, 0);
	vertices[4] = QVector3D (0, -width/4, 0);
	vertices[5] = QVector3D (width /4, 0, 0);
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
