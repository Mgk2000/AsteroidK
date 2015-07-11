QT       += core gui widgets
DEFINES += _QT_
TARGET = QtAsteroids
TEMPLATE = app
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder
INCLUDEPATH += c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game
SOURCES += main.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\flyingobject.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\ship.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\gun.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\view.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\math_helper.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\bullet.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\random.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\asteroid.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\patrol.cpp \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\patrolbullet.cpp \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\mat4.cpp \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\mutex.cpp \
    widget.cpp \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\text.cpp \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\texture.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/background.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/bonus.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/shipbonuses.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/sand.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/explosion.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/target.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/level.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/rectangle.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/bitmaptext.cpp \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/roundedrectangle.cpp

qtHaveModule(opengl) {
	QT += opengl

	SOURCES +=

	HEADERS +=

	RESOURCES +=
}

# install
target.path = c:\Projects\Android\AsteroidK\inst
INSTALLS += target

OTHER_FILES += \
	KVShader.vsh \
	vflyingshader.vsh \
	fflyingshader.fsh

HEADERS += \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\flyingobject.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\ship.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\gun.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\view.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\math_helper.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\bullet.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\random.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\asteroid.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\points.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\patrol.h \
        c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\patrolbullet.h \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\text.h \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\texture.h \
    c:\Projects\Android\Learn-OpenGLES-Tutorials-master\android\work\Asteroidsnative\game\mat4.h \
    widget.h \
    logmsg.h \
    globject.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/background.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/bonus.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/sand.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/explosion.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/target.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/rectangle.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/bitmaptext.h \
    c:\Projects\Android/Learn-OpenGLES-Tutorials-master/android/work/Asteroidsnative/game/roundedrectangle.h

RESOURCES += \
    AsteroidK.qrc
