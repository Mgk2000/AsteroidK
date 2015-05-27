#include "asteroid.h"
#include <math.h>
#include "view.h"
#include "intersect.h"
#include "random.h"
Asteroid::Asteroid(View * _view, Random* _random) : FlyingObject (_view, 1), random(_random)
{
//	init();
}


Asteroid::~Asteroid()
{
	delete[] rotatedVertices;
}

void Asteroid::init()
{
	initParams();
//-----------------------------------------------------
//	x=0.30;
//	y=0.0;
//	vx = -0.001;
//	vy = 0.00000;
//	rotateSpeed = 0.1;
//	speed =0;
//	nvertices = 3;
//	r=0.3;
//======================
	applyParams();

}

void Asteroid::initParams()
{
	x = random1().frandom(-1.0, 1.0);
	angle =  random1().frandom(M_PI * 0.8, M_PI * 1.2);
	speed = 0.003;
	//float qqq = sin(M_PI /6);
	vx = speed* sin (angle);
	r = random1().frandom(0.06, 0.10);
	y = 1.+0.5* r;
	if (x * vx  > 0 )
		vx = -vx;
	rotateSpeed = random1().frandom(-0.1, 0.1);
	vy = speed* cos (angle);
	nvertices = random1().irandom(40, 60);
//	nvertices = 3;
//	x=0;
//	vx=0;
}

void Asteroid::applyParams()
{
	vertices = new Point[nvertices];
	rotatedVertices = new Point[nvertices];
	for (int i=0; i< nvertices; i++)
	{
		float fi = M_PI*2 * i /nvertices;
		fi = fi + random1().frandom(-M_PI / nvertices /2., M_PI / nvertices /2);
		float r1 = r * random1().frandom(0.9, 1.1);
		vertices[i] = Point (r1 * sin(fi) , r1 * cos(fi), 0);
		rotatedVertices[i] = vertices[i];
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(QVector3D), vertices, GL_STATIC_DRAW);
	_color = QVector4D (0.3 + random1().frandom()*0.7 , 0.3 + random1().frandom()*0.7, 0.3 + random1().frandom()*0.7, 1.0);
}

void Asteroid::draw()
{
	QMatrix4x4 matrix;
	matrix.translate(x, y, 0);
	matrix.rotate(rotateAngle, 0.0, 0.0, 1.0);
	bool b = view->flyingprogram().bind();
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection * matrix);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	view->flyingprogram().enableAttributeArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	view->flyingprogram().setUniformValue("color", _color);
	glLineWidth(2.0);
	glDrawArrays(GL_LINE_LOOP, 0, nvertices);
	view->flyingprogram().disableAttributeArray(vertexLocation);

}

bool Asteroid::isPointInside(Point *p) const
{
	Point center(x,y, 0.0);
	return ::isInside(p, rotatedVertices, &center, nvertices, true);
}

bool Asteroid::out() const
{
	int x=0;
	bool b = y < -1.0;
	if (b)
		x=1;
	return b;
}

void Asteroid::moveStep()
{
	FlyingObject::moveStep();
	rotateAngle = rotateSpeed * live;
	rotatePoints(vertices, rotatedVertices, rotateAngle * M_PI /180, nvertices);
}

void Asteroid::getCurrentCoords(Point *_vertices, int *_nvertices) const
{
	*_nvertices = nvertices;
	for (int i=0; i< nvertices; i++)
	{
		_vertices[i].x = rotatedVertices[i].x+x;
		_vertices[i].y = rotatedVertices[i].y+y;
	}
}

Splinter::Splinter(View *view, Random* _random) : Asteroid (view, _random)
{

}

Splinter::~Splinter()
{

}

void Splinter::init(const Asteroid &parent, float fi)
{
//	float rr =
	r = parent.R() /2.;
	x = parent.X() + parent.R() * cos(fi);
	y = parent.Y() + parent.R() * sin(fi);
	float dv = 0.001;
	vx = parent.VX() + dv *  cos(fi);
	vy = parent.VY() + dv *  cos(fi);
	_color = parent.color();
	angle = atan2(vx, vy);
	nvertices = random->irandom(4,8);
	applyParams();
}

