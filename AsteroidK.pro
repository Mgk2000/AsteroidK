QT       += core gui widgets
DEFINES += _QT_
TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
	flyingobject.cpp \
	ship.cpp \
	gun.cpp \
	view.cpp \
	math_helper.cpp \
	bullet.cpp \
	random.cpp \
	asteroid.cpp \
	intersect.cpp \
	patrol.cpp \
	patrolbullet.cpp \
    mat4.cpp \
    widget.cpp

qtHaveModule(opengl) {
	QT += opengl

	SOURCES +=

	HEADERS +=

	RESOURCES +=
}

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
target.path = c:\Projects\Android\AsteroidK\inst
INSTALLS += target

OTHER_FILES += \
	KVShader.vsh \
	vflyingshader.vsh \
	fflyingshader.fsh

HEADERS += \
	flyingobject.h \
	ship.h \
	gun.h \
	view.h \
	math_helper.h \
	bullet.h \
	random.h \
	asteroid.h \
	intersect.h \
	points.h \
	patrol.h \
	patrolbullet.h \
    mat4.h \
    widget.h \
    logmsg.h
