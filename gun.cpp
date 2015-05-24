#include "gun.h"
#include <math.h>
#include "view.h"
#include "math_helper.h"
#include <QDebug>


Gun::Gun(View* _view) : view(_view)
{
	initializeGLFunctions();
	glGenBuffers(1, vboIds);
	init ();
}

Gun::~Gun()
{
	glDeleteBuffers(1, vboIds);
}
#define NP 65

void Gun::init()
{
	QVector3D points[NP];
	float w = 0.6;
	float h = 0.5;
	y = - 1 - h;
	r = sqrt(h * h + w * w);
	double fi0 = atan2(h, w);
	double fi1 = M_PI - 2* fi0;
	for (int i =0; i< NP; i++)
	{
		double fi = fi0 + fi1 * i / (NP-1);
		points [i] = QVector3D (r * cos(fi) ,y+ r * sin(fi), 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, NP * sizeof(QVector3D), points, GL_STATIC_DRAW);
	color = QVector4D (0.5, 0.5, 0.0, 1.0);
}

bool Gun::touched(float _x, float _y, float* fi) const
{
	const float delta = 0.15;
	float _r = sqrt(sqr(_x) + sqr (_y-y));
	float dr = r-_r;
	bool b = dr < delta && dr > -delta;
	qDebug() << "gun touched=" << b;
	return b;
}

void Gun::draw()
{
	QMatrix4x4 matrix3;
//	matrix3.translate(x, y, 0);
	bool b = view->flyingprogram().bind();
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection * matrix3);
	GLint err = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	err = glGetError();
	// Offset for position
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	err = glGetError();
	view->flyingprogram().enableAttributeArray(vertexLocation);
	err = glGetError();
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	err = glGetError();
	view->flyingprogram().setUniformValue("color", color);
	err = glGetError();
	glLineWidth(3.0);
	glDrawArrays(GL_LINE_STRIP, 0, NP);
	err = glGetError();
	err= err;
	QString qlog = view->flyingprogram().log();
	qlog = qlog;
}

