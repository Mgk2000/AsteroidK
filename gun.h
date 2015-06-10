#ifndef GUN_H
#define GUN_H
#ifdef _QT_
#include <QGLFunctions>
#endif
//#include <QGLShaderProgram>
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
