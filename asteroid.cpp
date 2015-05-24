#include "asteroid.h"
#include <math.h>
#include "view.h"

Asteroid::Asteroid(View * _view) : FlyingObject (_view)
{
	init();
}


Asteroid::~Asteroid()
{

}

void Asteroid::init()
{
	x = view->frandom(-0.2, 0.2);
	y = 1.1;
	angle =  view->frandom(M_PI * 0.8, M_PI * 1.2);
	speed = 0.001;
	float qqq = sin(M_PI /6);
	vx = speed* sin (angle);
	vy = speed* cos (angle);
	rotateSpeed = view->frandom(-0.001, 0.001);
	nvertices = view->irandom(6, 12);

	vertices = new QVector3D[nvertices];
	float r = view->frandom(0.2, 0.5);
	for (int i=0; i< nvertices; i++)
	{
		float fi = M_PI*2 * i /nvertices;
		fi = fi + view->frandom(-M_PI / nvertices /2., M_PI / nvertices /2);
		float r1 = r * view->frandom(0.7, 1.3);
		vertices[i] = QVector3D (r1 * sin(fi) , r1 * cos(fi), 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(QVector3D), vertices, GL_STATIC_DRAW);
	color = QVector4D (0.3+view->frandom()*0.7 , 0.3+view->frandom()*0.7, 0.3+view->frandom()*0.7, 1.0);
}

void Asteroid::draw()
{
	QMatrix4x4 matrix;
	matrix.translate(x, y, 0);
	bool b = view->flyingprogram().bind();
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection * matrix);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	view->flyingprogram().enableAttributeArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	view->flyingprogram().setUniformValue("color", color);
	glLineWidth(2.0);
	glDrawArrays(GL_LINE_LOOP, 0, nvertices);
}
