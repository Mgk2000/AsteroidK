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

#include "view.h"

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
	setAttribute(Qt::WA_AcceptTouchEvents);
}

View::~View()
{
}

bool View::event(QEvent *e)
{
	QEvent::Type etype = e->type();
	if (etype == QEvent::TouchBegin ||
		etype == QEvent::TouchUpdate ||
		etype == QEvent::TouchEnd ||
		etype == QEvent::TouchCancel
			)
	{
		QString s;
		switch (etype)
		{
		case QEvent::TouchBegin:
			s = "Begin "; break;
//		case QEvent::TouchUpdate:
//			s = "Update "; break;
//		case QEvent::TouchEnd:
//			s = "End "; break;
//		case QEvent::TouchCancel:
//			s = "Cancel "; break;
		default:
			break;
		}

		QTouchEvent* te = (QTouchEvent*) e;
		QList<QTouchEvent::TouchPoint> tpoints = te->touchPoints();
//		if (etype == QEvent::TouchBegin)
		//qDebug() << "Touch" << te->localPos().x() << e->localPos().y();
		//if (etype == QEvent::TouchUpdate || )
		{
			QList<QTouchEvent::TouchPoint> tpl = te->touchPoints();
			for (int i=0; i< tpl.count();i++)
			{
				QTouchEvent::TouchPoint p = tpl[i];
				switch (p.state())
				{
				case Qt::TouchPointPressed:
					processPress(p.pos().x(),  p.pos().y());
					break;
				case Qt::TouchPointMoved:
					processMove(p.pos().x(),  p.pos().y());
					break;
				case Qt::TouchPointReleased:
					processRelease(p.pos().x(),  p.pos().y());
					break;
				default:
					break;
				}
				s += QString("x=%1 y=%2       ").arg(p.pos().x()).arg(p.pos().y());
			}
			//qDebug() << s ;
		}
		e->accept();
		return true;
	}
	return QGLWidget::event(e);
}

//! [0]

void View::mousePressEvent(QMouseEvent *e)
{
	processPress(e->localPos().x(),e->localPos().y());
}
void View::mouseReleaseEvent(QMouseEvent *e)
{
	processRelease(e->localPos().x(),e->localPos().y());
}
void View::mouseMoveEvent(QMouseEvent *e)
{
	processMove(e->localPos().x(),e->localPos().y());
}

void View::processMove(int x, int y)
{
	float fx, fy;
	screenToView(x,y, &fx, &fy);
	if (ship->touched(fx, fy))
	{
		shipDragging = true;
		ship->setX(fx);
		updateGL();
//		qDebug() << "posXY=" << e->localPos().x() << e->localPos().y() << "  ShipX=" << ship->X();
	}
}

void View::processPress(int x, int y)
{
	float fx, fy;
	screenToView(x,y , &fx, &fy);
	float fi;
	if (gun->touched(fx, fy, &fi))
	{

	}
}

void View::processRelease(int x, int y)
{
	float fx, fy;
	screenToView(x,y, &fx, &fy);
	if (ship->touched(fx, fy))
		shipDragging = false;

}

void View::timerEvent(QTimerEvent *)
{
	updateGL();
}


void View::initializeGL()
{
	initializeGLFunctions();
	qglClearColor(Qt::black);
	initShaders();

	// Enable depth buffer
//	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);

	// Enable back face culling
//	glEnable(GL_CULL_FACE);

	ship = new Ship (this);
	//ship->init();
	gun = new Gun (this);
	// Use QBasicTimer because its faster than QTimer
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

void View::screenToView(int x, int y, float *fx, float *fy) const
{
	*fx = 2.0 * (x - width()/2) / width() * aspect;
	*fy = - 2.0 * (y - height()/2) * 1.0 / height();
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
