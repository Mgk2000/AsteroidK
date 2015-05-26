QT       += core gui widgets

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
    patrolbullet.cpp

qtHaveModule(opengl) {
    QT += opengl

    SOURCES +=

    HEADERS +=

    RESOURCES += \
        shaders.qrc \
        textures.qrc
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

OTHER_FILES += \
    KVShader.vsh \
    KFShader.fsh \
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
    patrolbullet.h
