#include "patrol.h"
#include "view.h"
#include <math.h>
#include <QDebug>

Patrol::Patrol(View* _view) : FlyingObject (_view, 2)
{
//	init();
}

Patrol::~Patrol()
{

}
#define NP 24
void Patrol::init()
{
	bool left  = random1().frandom() <=0.5;
	y= 0.8;
	x = left ? view->left()-0.1 : view->right() + 0.1;
	vx = left ? 0.003 : -0.003;
	vy =0;
	r = 0.05;
	QVector3D points[NP];
	for (int i =0; i< NP; i++)
	{
		double fi = M_PI * i * 2 / (NP-1);
		points [i] = QVector3D (r * cos(fi) , r * sin(fi) * 0.6, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	GLint err = glGetError();

	glBufferData(GL_ARRAY_BUFFER, NP * sizeof(QVector3D), points, GL_STATIC_DRAW);
	err = glGetError();
	_color = QVector4D (0.0, 0.7, 1.0, 1.0);
	width = r * 1.3;
	points[0]= QVector3D (-width, 0.0, 0.0);
	points[1]= QVector3D (width, 0.0, 0.0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
	err = glGetError();
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(QVector3D), points, GL_STATIC_DRAW);
	err = glGetError();
}

void Patrol::draw()
{
	QMatrix4x4 matrix;
	matrix.translate(x, y, 0);
	bool b = view->flyingprogram().bind();
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection *  matrix);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	view->flyingprogram().enableAttributeArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	view->flyingprogram().setUniformValue("color", color());
	glLineWidth(2.0);
	glDrawArrays(GL_LINE_LOOP, 0, NP);
	//return;
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
	offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	view->flyingprogram().enableAttributeArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	view->flyingprogram().setUniformValue("color", color());
	glLineWidth(2.0);
	glDrawArrays(GL_LINES, 0, 2);
}

bool Patrol::out() const
{
	return x< view->left()-0.2 || x > view->right() + 0.2;
}

void Patrol::getCurrentCoords(Point *_vertices, int *_nvertices) const
{
	*_nvertices = 4;
//	_vertices[0] = Point (-width +x, y, 0);
//	_vertices[1] = Point (x, r+y, 0);
//	_vertices[2] = Point (width +x, y, 0);
//	_vertices[3] = Point (x, -r + y, 0);
	_vertices[0] = Point (-width +x, r+y, 0);
	_vertices[1] = Point (x+width, r+y, 0);
	_vertices[2] = Point (width +x, y-r, 0);
	_vertices[3] = Point (x-width, -r + y, 0);
}
