#include "flyingobject.h"
#include "view.h"
#include "math.h"
#include "intersect.h"
#include "logmsg.h"

float FlyingObject::v0=1.0;

FlyingObject::FlyingObject(View* _view, int _nbos): nvbos (_nbos), vertices(0), indices(0), nvertices(0), nindices(0), view(_view),
	rotateSpeed(0.0f), live(0), angle(0.f), speed (0.f)
{
#ifdef _QT_
	initializeGLFunctions();
#endif
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
#ifdef _QT_
	initializeGLFunctions();
#endif
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
    speed = speed * v0;
	vx = speed* sin(angle);
	vy = speed* cos(angle);
}

void FlyingObject::draw()
{
}

void FlyingObject::moveStep(float delta)
{
    x = x + vx * delta;
    y = y + vy * delta;
	live++;
}

void FlyingObject::swapColor()
{
	_color = Point4D (1-_color.x(), 1-_color.y(), 1- _color.z(), 1);
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
	glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(Point), vertices, GL_STATIC_DRAW);

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

void FlyingObject::drawTriangles ()
{
	Mat4 _matrix1;
	_matrix1.translate(x, y, 0);
	_matrix1 = view->projection1 * _matrix1;
//	glUseProgram(view->flyingprogram().programId());
	glUseProgram(view->program());
	glUniformMatrix4fv(view->matrixlocation(), 1, false, (const GLfloat*) &_matrix1);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glEnableVertexAttribArray(view->vertexlocation());
	glVertexAttribPointer(view->vertexlocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Point), (const void *) 0);
	Point4D col = color();
	glUniform4fv(view->colorlocation() ,1 , (GLfloat*) &col );
	glDrawElements(GL_TRIANGLES, nindices , GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(view->vertexlocation());
}

void FlyingObject::drawLines(int how, uint vbo, int npoints, const Point4D& _color, float _width, float angle)
{
//	int err;
	Mat4 _matrix1;
	_matrix1.translate(x, y, 0);
	_matrix1 = view->projection1 * _matrix1;
	//	glUseProgram(view->flyingprogram().programId());
		glUseProgram(view->program());
	if (angle !=0.0)
		_matrix1.rotateZ(angle);
	glUniformMatrix4fv(view->matrixlocation(), 1, false, (const GLfloat*) &_matrix1);
//	err = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	err = glGetError();
	glEnableVertexAttribArray(view->vertexlocation());
//	err = glGetError();
	glVertexAttribPointer(view->vertexlocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Point), (const void *) 0);
//	err = glGetError();
	Point4D col = _color;
	glUniform4fv(view->colorlocation() ,1 , (GLfloat*) &col );
//	err = glGetError();
	glLineWidth(_width);
//	err = glGetError();
	glDrawArrays(how, 0, npoints);
//	err = glGetError();
//	LOGD("err=%d", err);
	glDisableVertexAttribArray(view->vertexlocation());
//	err = glGetError();
}

void FlyingObject::showMatrix(Mat4 &m)
{
/*	for (int i=0; i<4; i++)
	{
		QString s;
		for (int j=0; j< 4; j++)
			s=s+QString("%1 ").arg(m.m[i][j]);
		qDebug() << s;
	}
	qDebug() << "-----";*/
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

