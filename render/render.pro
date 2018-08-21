QT       += core gui widgets

TARGET = render
TEMPLATE = app

SOURCES += \
    src/mainwidget.cpp \
    src/modelgeometry.cpp \
    src/modelstate.cpp \
    src/main.cpp \    
    src/model.cpp \
    src/modelmanager.cpp \
    src/engine.cpp \
    src/scenestate.cpp

HEADERS += \
    src/mainwidget.h \
    src/modelstate.h \
    src/modelgeometry.h \
    src/model.h \
    src/modelmanager.h \
    src/engine.h \
    src/scenestate.h

RESOURCES += \
    shaders.qrc 


