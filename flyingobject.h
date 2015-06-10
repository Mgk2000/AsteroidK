#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H
#ifdef _QT_
#include <QGLFunctions>
#include <QGLShaderProgram>
#else
#include <jni.h>
#include <GLES2/gl2.h>
typedef  unsigned int uint;
#endif
#include "points.h"
class Random;
class View;
class Mat4;
class FlyingObject
#ifdef _QT_
		: protected QGLFunctions
#endif
{
public:
	FlyingObject(View* _view, int _nbos);
	FlyingObject(View* _view, int _nbos, float _x, float _y, float _speed, float _angle);
	virtual ~FlyingObject();
	virtual void init();
	virtual void draw();
    virtual void moveStep(float delta);
	float X() const {return x;}
	float Y() const {return y;}
	float VX() const {return vx;}
	float VY() const {return vy;}
	void swapColor();
	void setXY(float _x, float _y) {x = _x; y=_y;}
	void setSpeedXY(float _vx, float _vy) {vx = _vx; vy=_vy;}
	void setColor(float r , float g , float b) {_color = Point4D (r,g,b,1.0);}
	void setColor( const Point4D&  __color) {_color = __color;}
	virtual const Point4D&  color() const {return _color;}
	virtual void getCurrentCoords (Point * _vertices, int* _nvertices ) const;
	bool isIntersects(const FlyingObject& obj)  const;
	virtual bool isPointInside( Point* p) const;
    static float v0;
protected:
	float x,y,angle;
	uint* vboIds;
	int nvbos;
	Point* vertices;
	int nvertices;
	GLushort* indices;
	int nindices;
	Point4D _color;
	void fill_vbos();
	View* view;
	float rotateSpeed;
	int live;
	float speed;
	float vx, vy;
	float r;
	Random &random1() const;
	Random &random2() const;
	void drawTriangles();
	void drawLines(int how, uint vbo, int npoints, const Point4D& color, float _width, float angle = 0.0);
	void showMatrix (Mat4& m);
};


#endif // FLYINGOBJECT_H
