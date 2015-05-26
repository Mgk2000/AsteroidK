#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QGLFunctions>
#include <QGLShaderProgram>
#include "points.h"
class Random;
class View;
class FlyingObject : protected QGLFunctions
{
public:
	FlyingObject(View* _view, int _nbos);
	FlyingObject(View* _view, int _nbos, float _x, float _y, float _speed, float _angle);
	virtual ~FlyingObject();
	virtual void init();
	virtual void draw();
	virtual void moveStep();
	float X() const {return x;}
	float Y() const {return y;}
	float VX() const {return vx;}
	float VY() const {return vy;}
	void swapColor();
	void setXY(float _x, float _y) {x = _x; y=_y;}
	void setSpeedXY(float _vx, float _vy) {vx = _vx; vy=_vy;}
	void setColor(float r , float g , float b) {_color = QVector4D (r,g,b,1.0);}
	void setColor( const QVector4D&  __color) {_color = __color;}
	virtual const QVector4D&  color() const {return _color;}
	virtual void getCurrentCoords (Point * _vertices, int* _nvertices ) const;
	bool isIntersects(const FlyingObject& obj)  const;
	virtual bool isPointInside( Point* p) const;

protected:
	float x,y,angle;
	uint* vboIds;
	int nbos;
	//QVector3D* vertices;
	Point* vertices;
	int nvertices;
	GLushort* indices;
	int nindices;
	QVector4D _color;
	void fill_vbos();
	View* view;
	float rotateSpeed;
	int live;
	float speed;
	float vx, vy;
	float r;
	Random &random1() const;
	Random &random2() const;
};


#endif // FLYINGOBJECT_H
