#include "flyingobject.h"
#include "view.h"
#include "math.h"
#include "intersect.h"
FlyingObject::FlyingObject(View* _view): vertices(0), indices(0), nvertices(0), nindices(0), view(_view),
	rotateSpeed(0.0f), live(0), angle(0.f), speed (0.f)
{
	initializeGLFunctions();
	glGenBuffers(2, vboIds);
}

FlyingObject::FlyingObject(View *_view, float _x, float _y, float _speed, float _angle):
	vertices(0), indices(0), nvertices(0), nindices(0), view(_view),
	rotateSpeed(0.0f), live(0), angle(_angle), speed (_speed), x(_x), y(_y)
{
	initializeGLFunctions();
	glGenBuffers(2, vboIds);
	vx = speed* sin(angle);
	vy = speed* cos(angle);
}

FlyingObject::~FlyingObject()
{
	glDeleteBuffers(2, vboIds);
	if (vertices)
		delete[] vertices;
	if (indices)
		delete[] indices;
}

void FlyingObject::init()
{
//	initializeGLFunctions();
//	glGenBuffers(2, vboIds);

}

void FlyingObject::draw()
{
	QMatrix4x4 matrix3;
	matrix3.translate(x, y, 0);
	bool b = view->flyingprogram().bind();
	view->flyingprogram().setUniformValue("mvp_matrix", view->projection * matrix3);
	GLint err = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	err = glGetError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
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
	view->flyingprogram().setUniformValue("color", color());
	err = glGetError();
	// Draw cube geometry using indices from VBO 1
	glDrawElements(GL_TRIANGLES, nindices , GL_UNSIGNED_SHORT, 0);
	err = glGetError();
	err= err;
	QString qlog = view->flyingprogram().log();
	qlog = qlog;
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
			::isInside(&myvertices[i],overtices,&ocenter,onvertices, false);
			return true;
		}
	for (int i =0; i< onvertices; i++)
		if (::isInside(&overtices[i],myvertices,&mycenter,mynvertices, false))
			return true;

	return false;

}
