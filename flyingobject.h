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
	virtual ~FlyingObject();
	virtual void init();
	virtual void draw();
	float X() const {return x;}
	float Y() const {return y;}

protected:
	float x,y,angle;
	GLuint vboIds[2];
	QVector3D* vertices;
	int nvertices;
	GLushort* indices;
	int nindices;
	QVector4D color;
	void fill_vbos();
	View* view;
};

#endif // FLYINGOBJECT_H
