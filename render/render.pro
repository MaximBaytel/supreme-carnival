QT       += core gui widgets

TARGET = render
TEMPLATE = app

SOURCES += \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/main.cpp \
    src/model.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/model.h

RESOURCES += \
    shaders.qrc 


