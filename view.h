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

#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QBasicTimer>
#include <QGLShaderProgram>
#include <list>
#include "points.h"
#include "random.h"
#include "mat4.h"

class Ship;
class Gun;
class Bullet;
class Random;
class Asteroid;
class GeometryEngine;
class Patrol;
struct BulletInfo
{
	Bullet* bullet;
	BulletInfo* next;
};

class View : public QGLWidget, protected QGLFunctions
{
	Q_OBJECT

public:
	explicit View(QWidget *parent = 0);
	~View();
	//QGLShaderProgram& flyingprogram() {return _flyingprogram;}
	Mat4 projection1;
	float fieldWidth() const {return aspect;}
	Random& random1() {return _random1;}
	Random& random2() {return _random2;}
	void checkShoots();
	float left() const {return -0.6;}
	float right() const {return 0.6;}
	float top() const {return 1.0;}
	float bottom() const {return -1.0;}
	void patrolShoot (Patrol* _patrol);

	void breakShip();
	int matrixlocation() const {return _matrixlocation;}
	int colorlocation() const {return _colorlocation;}
	int vertexlocation() const {return _vertexlocation;}
	GLuint program() const {return _program;}
private:
	bool event(QEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *);

	void processMove (int x, int y);
	void processPress (int x, int y);
	void processRelease (int x, int y);

	void timerEvent(QTimerEvent *e);

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	GLuint createShader(GLenum shaderType, const char* src);
	GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);
	void initShaders();
	void screenToView(int x, int y, float* fx, float * fy) const;
	void shoot (float angle);
	std::list <Asteroid*> asteroids;
	void addAsteroid(Asteroid* asteroid);
	void deleteAsteroid(Asteroid* asteroid);
	int asteroidAppearTime;
	std::list <Bullet*> bullets;
	void addBullet(Bullet* bullet);
	void deleteBullet(Bullet* bullet);
	void createSplinters(Asteroid* asteroid);
	Patrol* patrol;

private:
	QBasicTimer timer;
	QGLShaderProgram  _flyingprogram;
	GLuint _program;

//	GLuint texture;


	QVector2D mousePressPosition;
//	float shiftX;
	Ship* ship;
	Gun * gun;
	float aspect;
	bool shipDragging;
	Random _random1, _random2;
	int nticks;
	int dieticks;
	int _matrixlocation, _vertexlocation, _colorlocation;
};

#endif // VIEW_H
