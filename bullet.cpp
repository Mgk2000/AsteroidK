#include "bullet.h"
#include <math.h>
#include "view.h"

#include "logmsg.h"
Bullet::Bullet(View* view, float _x, float _y, float _angle)
    : FlyingObject(view, 1, _x, _y, 1.0f, _angle)

{

}

Bullet::~Bullet()
{

}

void Bullet::init()
{
	rotateSpeed = 0.0f;
	vertices = new Point[2];
	length = 0.1f;
	vertices[1] = Point (0 , 0, 0);
	vertices[0] = Point (length * sin(angle), length * cos (angle), 0);
	nvertices = 2;

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Point), vertices, GL_STATIC_DRAW);
	_color = Point4D (0.9, 0.9, 0.0, 1.0);
	FlyingObject::init();

}

void Bullet::draw()
{
	drawLines(GL_LINE_STRIP, vboIds[0], 2, color(), 2.0);
}

Point Bullet::top() const
{
	return Point (x + length * sin(angle),y +length * cos (angle) ,0);
}

bool Bullet::out() const
{
    return x <-0.6 || x > 0.6 || y > 1.0;
}

void Bullet::moveStep(float delta)
{
    float sx = x;
    float sy = y;
    FlyingObject::moveStep(delta);
//    qDebug() << "bullet dx, dy=" << x-sx << y-sy;
//    LOGD("bullet dx, dy= %f %f", x-sx , y-sy);

}
