#include "intersect.h"
#include <math.h>
#include <QDebug>

bool isInside(Point* p, Point* poly, Point* center, int npoints, float angle)
{
	for (int i=0; i< npoints; i++)
	{
		Point p1, p2;
		int i1 = (i+1) % npoints;
		p1 = poly[i];
		p1.x = p1.x + center->x;
		p1.y = p1.y + center->y;
		p2 = poly[i1];
		p2.x = p2.x + center->x;
		p2.y = p2.y + center->y;
		if (isInsideTriangle (p, &p1, &p2, center))
			return true;
	}
	return false;
}

//int a = (x[1] - x[0]) * (y[2] - y[1]) - (x[2] - x[1]) * (y[1] - y[0]);
//int b = (x[2] - x[0]) * (y[3] - y[2]) - (x[3] - x[2]) * (y[2] - y[0]);
//int c = (x[3] - x[0]) * (y[1] - y[3]) - (x[1] - x[3]) * (y[3] - y[0]);


bool isInsideTriangle(Point *p, Point *p1, Point *p2, Point *p3)
{
	float d1 = (p1->x - p->x) * (p2->y - p1->y) - (p2->x - p1->x) * (p1->y - p->y);
	float d2 = (p2->x - p->x) * (p3->y - p2->y) - (p3->x - p2->x) * (p2->y - p->y);
	if (d1*d2 < 0) return false;
	float d3 = (p3->x - p->x) * (p1->y - p3->y) - (p1->x - p3->x) * (p3->y - p->y);
	bool b = d2*d3>=0;
	if (b)
		qDebug() << b;
	return b;
}

//x = x * cos(a) - y * sin(a)
//y = x * sin(a) + y * cos(a)
void rotatePoint(Point *ps, Point* pd, double sina , double cosa)
{
	pd->x = ps->x* cosa - ps->y * sina;
	pd->y = ps->x * sina +ps->y * cosa;
}
void rotatePoints(Point *ps, Point* pd, double angle, int np)
{
	double sina = sin(angle);
	double cosa = cos(angle);
	for (int i=0; i<np; i++)
		rotatePoint(&ps[i], &pd[i], sina, cosa);
}
