QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    Kmainwidget.cpp \
    flyingobject.cpp \
    ship.cpp \
    gun.cpp

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
    Kmainwidget.h \
    flyingobject.h \
    ship.h \
    gun.h
