#ifndef GUN_H
#define GUN_H
#include <QVector2D>
#include <QVector3D>
#include <QGLFunctions>
#include <QGLShaderProgram>
class View;

class Gun : protected QGLFunctions
{
public:
	Gun(View* );
	~Gun();
	void draw();
	void init();
private:
	float y, r;
	View* view;
	uint vboIds[1];
	QVector4D color;

};

#endif // GUN_H
