#ifndef GUN_H
#define GUN_H
#include <QVector2D>
#include <QVector3D>
#include <QGLFunctions>
#include <QGLShaderProgram>
#include "flyingobject.h"

class View;

class Gun : public FlyingObject
{
public:
	Gun(View* );
	~Gun();
	void draw();
	void init();
	bool touched(float _x, float _y, float* fi) const;
private:
	float r;
};

#endif // GUN_H
