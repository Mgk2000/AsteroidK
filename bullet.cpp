#include "bullet.h"
#include <math.h>
#include "view.h"
Bullet::Bullet(View* view, float _x, float _y, float _angle) : FlyingObject(view, _x, _y, 0.02f, _angle)

{
	init();
}

Bullet::~Bullet()
{

}

void Bullet::init()
{
	rotateSpeed = 0.0f;
	vertices = new Point[2];
	float length = 0.1f;
	vertices[0] = Point (0 , 0, 0);
	vertices[1] = Point (length * sin(angle), length * cos (angle), 0);
	nvertices = 2;

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(QVector3D), vertices, GL_STATIC_DRAW);
	color = QVector4D (0.9, 0.9, 0.0, 1.0);

}

void Bullet::draw()
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
	glLineWidth(1.0);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
}

Point Bullet::top() const
{
	return Point (x,y,0);
}

bool Bullet::out() const
{
	return x <-0.6 || x > 0.6 || y > 1.0;
}
