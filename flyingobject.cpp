#include "flyingobject.h"
#include "view.h"
#include "math.h"
#include "intersect.h"

FlyingObject::FlyingObject(View* _view, int _nbos): nvbos (_nbos), vertices(0), indices(0), nvertices(0), nindices(0), view(_view),
	rotateSpeed(0.0f), live(0), angle(0.f), speed (0.f)
{
	initializeGLFunctions();
	if (nvbos)
	{
		vboIds = new uint[nvbos];
		glGenBuffers(nvbos, vboIds);
	}
}

FlyingObject::FlyingObject(View *_view, int _nbos, float _x, float _y, float _speed, float _angle):
	nvbos (_nbos), vertices(0), indices(0), nvertices(0), nindices(0), view(_view),
	rotateSpeed(0.0f), live(0), angle(_angle), speed (_speed), x(_x), y(_y)
{
	initializeGLFunctions();
	if (nvbos)
	{
		vboIds = new uint[nvbos];
		glGenBuffers(nvbos, vboIds);
	}

}

FlyingObject::~FlyingObject()
{
	if (nvbos)
	{
		glDeleteBuffers(nvbos, vboIds);
		delete[] vboIds;
	}
	if (vertices)
		delete[] vertices;
	if (indices)
		delete[] indices;
}

void FlyingObject::init()
{
	vx = speed* sin(angle);
	vy = speed* cos(angle);
}

void FlyingObject::draw()
{
	int err;
	QMatrix4x4 matrix3;
	matrix3.translate(x, y, 0);
	bool b = view->flyingprogram().bind();
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection * matrix3);

	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;

	// Offset for position
	quintptr offset = 0;

	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertexLocation = view->flyingprogram().attributeLocation("aVertexPosition");
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	view->flyingprogram().enableAttributeArray(vertexLocation);
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	view->flyingprogram().setUniformValue("color", color());
	err= glGetError(); if (err) qDebug() << "glGetError=" << err;
	glDrawElements(GL_TRIANGLES, nindices , GL_UNSIGNED_SHORT, 0);
	err= glGetError(); if (err) qDebug() << "glGetError=" << err << "nindices=" << nindices;
	view->flyingprogram().disableAttributeArray(vertexLocation);

//	err= err;
//	QString qlog = view->flyingprogram().log();
//	qlog = qlog;
}

void FlyingObject::moveStep()
{
	x = x + vx;
	y = y + vy;
	live++;
}

void FlyingObject::swapColor()
{
	_color = QVector4D (1-_color.x(), 1-_color.y(), 1- _color.z(), 1);
}

void FlyingObject::getCurrentCoords(Point *_vertices, int *_nvertices) const
{
	*_nvertices = nvertices;
	for (int i=0; i< nvertices; i++)
	{
		_vertices[i].x = vertices[i].x+x;
		_vertices[i].y = vertices[i].y+y;
	}
}

void FlyingObject::fill_vbos()
{
	// Transfer vertex data to VBO 0
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(QVector3D), vertices, GL_STATIC_DRAW);

	// Transfer index data to VBO 1
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nindices * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

Random& FlyingObject::random1() const
{
	return view->random1();
}

Random &FlyingObject::random2() const
{
	return view->random2();
}
bool FlyingObject::isIntersects(const FlyingObject& obj) const
{
	Point mycenter (X(), Y());
	Point ocenter (obj.X(), obj.Y());
//	Point ocenter (0, 0);
	int onvertices;
	Point overtices[100];
	Point myvertices [100];
	int mynvertices;
	obj.getCurrentCoords(overtices, &onvertices);
	getCurrentCoords(myvertices, &mynvertices);
	for (int i =0; i< mynvertices; i++)
		if (::isInside(&myvertices[i],overtices,&ocenter,onvertices, false))
		{
//			::isInside(&myvertices[i],overtices,&ocenter,onvertices, false);
			return true;
		}
	for (int i =0; i< onvertices; i++)
		if (::isInside(&overtices[i],myvertices,&mycenter,mynvertices, false))
			return true;

	return false;

}

bool FlyingObject::isPointInside(Point *p) const
{
	Point myvertices [100];
	int mynvertices;
	getCurrentCoords(myvertices, &mynvertices);
	Point mycenter (X(), Y());
	return ::isInside(p, myvertices, &mycenter,mynvertices, false);
}

