#ifndef INTERSECT_H
#define INTERSECT_H
#include "points.h"


bool isInsideTriangle (Point* p, Point* p1, Point* p2, Point* p3);
bool isInside (Point* p, Point* poly, Point* center, int npoints, bool relative);
void rotatePoint(Point *ps, Point* pd, double sina , double cosa);
void rotatePoints(Point *ps, Point* pd, double angle, int np);
#endif // INTERSECT_H
