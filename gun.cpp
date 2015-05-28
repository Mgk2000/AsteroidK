#include "gun.h"
#include <math.h>
#include "view.h"
#include "math_helper.h"
#include <QDebug>


Gun::Gun(View* _view) :  FlyingObject(_view, 1)
{
	init ();
}

Gun::~Gun()
{

}
#define NP 65

void Gun::init()
{
	Point points[NP];
	float w = 0.6;
	float h = 0.0;
	y = - 1 - h;
	r = sqrt(h * h + w * w);
	double fi0 = atan2(h, w);
	double fi1 = M_PI - 2* fi0;
	for (int i =0; i< NP; i++)
	{
		double fi = fi0 + fi1 * i / (NP-1);
		points [i] = Point (r * cos(fi) , r * sin(fi), 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, NP * sizeof(Point), points, GL_STATIC_DRAW);
	_color = Point4D (0.5, 0.5, 0.0, 1.0);
}

bool Gun::touched(float _x, float _y, float* fi) const
{
	const float delta = 0.15;
	float _r = sqrt(sqr(_x) + sqr (_y-y));
	float dr = r-_r;
	bool b = dr < delta && dr > -delta;
	//qDebug() << "gun touched=" << b;
	if (b)
	{
		*fi = (float) atan2(_x,_y-y);
	}
	return b;
}

void Gun::draw()
{
	drawLines(GL_LINE_STRIP, vboIds[0], NP, color(), 4.0);
}

