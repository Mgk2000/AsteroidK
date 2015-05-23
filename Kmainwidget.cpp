/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Kmainwidget.h"

#include <QMouseEvent>

#include <math.h>
#include "ship.h"
#include "gun.h"

View::View(QWidget *parent) :
	QGLWidget(parent),
	 shipDragging(false)
{
//	setAttribute(Qt::WA_PaintOnScreen);
//	setAttribute(Qt::WA_NoSystemBackground);
//	setAutoBufferSwap(false);
//	setHeight(800);
	this->setGeometry(geometry().x() + 100, geometry().y() +200, 480, 800);

}

View::~View()
{
}

//! [0]
#if 0
void View::mousePressEvent(QMouseEvent *e)
{
}
#endif
void View::mouseReleaseEvent(QMouseEvent *e)
{
	shipDragging = false;
}
bool View::testShipTouched(int x, int y) const
{
	float xxx = 2.0 * (x - width()/2) / width() * aspect;
	const float delta = 0.15;
	float dx = xxx-ship->X();
	if (dx > delta || dx < -delta)
		return false;
	float yyy = - 2.0 * (y - height()/2) * 1.0 / height();
	float dy = yyy-ship->Y();
	if (dy > delta || dy < -delta)
		return false;
	return true;
}
void View::mouseMoveEvent(QMouseEvent *e)
{
	if (testShipTouched(e->localPos().x(), e->localPos().y()) || shipDragging)
	{
		shipDragging = true;
		QVector2D diff = QVector2D(e->localPos());

		QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
		float xxx = 2 * (e->localPos().x() - width()/2) * 1.0 / width() * aspect;
		ship->setX(xxx);
		updateGL();
		qDebug() << "posXY=" << e->localPos().x() << e->localPos().y() <<  "x=" << n.x() << "  ShipX=" << ship->X();

	}
}
//! [0]

//! [1]
void View::timerEvent(QTimerEvent *)
{
	updateGL();
}
//! [1]

void View::initializeGL()
{
//	return;
	initializeGLFunctions();
	qglClearColor(Qt::black);
	initShaders();

//! [2]
	// Enable depth buffer
//	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);

	// Enable back face culling
//	glEnable(GL_CULL_FACE);
//! [2]

//	geometries.init();

	// Use QBasicTimer because its faster than QTimer
	ship = new Ship (this);
	//ship->init();
	gun = new Gun (this);
	timer.start(12, this);
}

//! [3]
void View::initShaders()
{
	// Compile vertex shader
	if (!_flyingprogram.addShaderFromSourceFile(QGLShader::Vertex, ":/vflyingshader.vsh"))
		close();

	// Compile fragment shader
	if (!_flyingprogram.addShaderFromSourceFile(QGLShader::Fragment, ":/fflyingshader.fsh"))
		close();

	// Link shader pipeline
	if (!_flyingprogram.link())
		close();

}
//! [3]

void View::resizeGL(int w, int h)
{
	// Set OpenGL viewport to cover whole widget
	glViewport(0, 0, w, h);

	// Calculate aspect ratio
	//qreal aspect = qreal(w) / qreal(h ? h : 1);
	aspect = w * 1.0 / h;
	// Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
//	const qreal zNear = 3.0, zFar = 10.0, fov = 45.0;

	// Reset projection
	projection.setToIdentity();


	// Set perspective projection
//	projection.perspective(fov, aspect, zNear, zFar);
//	projection.ortho(0.0,  480.0 , 0.0,800.0, 1999, -1999 );
	projection.ortho(- aspect, aspect , -1.0, 1.0 , -1999., 1999. );

}
//! [5]
void View::paintGL()
{

	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//! [6]
	ship->draw();
	gun->draw();
}
