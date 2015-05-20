QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    Kgeometryengine.cpp \
    Kmainwidget.cpp \
    flyingobject.cpp \
    ship.cpp

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
    KFShader.fsh

HEADERS += \
    Kgeometryengine.h \
    Kmainwidget.h \
    flyingobject.h \
    ship.h
