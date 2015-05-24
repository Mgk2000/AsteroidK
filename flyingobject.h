#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H
#include <QVector2D>
#include <QVector3D>
#include <QGLFunctions>
#include <QGLShaderProgram>
class View;
class FlyingObject : protected QGLFunctions
{
public:
	FlyingObject(View* _view);
	FlyingObject(View* _view, float _x, float _y, float _speed, float _angle);
	virtual ~FlyingObject();
	virtual void init();
	virtual void draw();
	virtual void moveStep();
	float X() const {return x;}
	float Y() const {return y;}

protected:
	float x,y,angle;
	uint vboIds[2];
	QVector3D* vertices;
	int nvertices;
	GLushort* indices;
	int nindices;
	QVector4D color;
	void fill_vbos();
	View* view;
	float rotateSpeed;
	int live;
	float speed;
	float vx, vy;
};


#endif // FLYINGOBJECT_H
