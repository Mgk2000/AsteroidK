#ifndef POINTS_H
#define POINTS_H

struct Point3D
{
	Point3D () : x (0.0), y(0.0), z(0.0) {}
	Point3D (float _x, float _y, float _z) : x (_x), y(_y), z(_z) {}
	float x,y,z;

};
typedef Point3D Point;
#endif // POINTS_H
