#ifndef INTERSECT_H
#define INTERSECT_H
#include "points.h"


bool isInsideTriangle (Point* p, Point* p1, Point* p2, Point* p3);
bool isInside (Point* p, Point* poly, Point* center, int npoints, float angle = 0.0);

#endif // INTERSECT_H
