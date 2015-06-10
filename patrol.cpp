#include "patrol.h"
#include "view.h"
#include <math.h>

Patrol::Patrol(View* _view) : FlyingObject (_view, 2)
{
//	init();
}

Patrol::~Patrol()
{

}
#define NP 24
void Patrol::init()
{
	bool left  = random1().frandom() <=0.5;
	y= 0.8;
	x = left ? view->left()-0.1 : view->right() + 0.1;
    vx = left ? 0.2 : -0.2;
	vy =0;
	r = 0.05;
	Point3D points[NP];
	for (int i =0; i< NP; i++)
	{
		double fi = M_PI * i * 2 / (NP-1);
		points [i] = Point3D (r * cos(fi) , r * sin(fi) * 0.6, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, NP * sizeof(Point3D), points, GL_STATIC_DRAW);
	_color = Point4D (0.0, 0.7, 1.0, 1.0);
	width = r * 1.3;
	points[0]= Point3D (-width, 0.0, 0.0);
	points[1]= Point3D (width, 0.0, 0.0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Point3D), points, GL_STATIC_DRAW);
}

void Patrol::draw()
{
	drawLines(GL_LINE_LOOP,vboIds[0],NP,color(), 3.0);
	drawLines(GL_LINE_LOOP,vboIds[1],2,color(), 2.0);
	return;
}

bool Patrol::out() const
{
	return x< view->left()-0.2 || x > view->right() + 0.2;
}

void Patrol::moveStep(float delta)
{
    FlyingObject::moveStep(delta);
	float dw = 0.1;
	if ((x>-view->left() && x<-view->left()+dw) ||
		(x>-view->right()-dw && x<-view->right()))
		view->patrolShoot(this);

}

void Patrol::getCurrentCoords(Point *_vertices, int *_nvertices) const
{
	*_nvertices = 4;
	_vertices[0] = Point (-width +x, r+y, 0);
	_vertices[1] = Point (x+width, r+y, 0);
	_vertices[2] = Point (width +x, y-r, 0);
	_vertices[3] = Point (x-width, -r + y, 0);
}
