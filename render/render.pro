QT       += core gui widgets

TARGET = render
TEMPLATE = app

SOURCES += \
    src/mainwidget.cpp \
    src/modelgeometry.cpp \
    src/modelstate.cpp \
    src/main.cpp \    
    src/model.cpp

HEADERS += \
    src/mainwidget.h \
    src/modelstate.h \
    src/modelgeometry.h \
    src/model.h

RESOURCES += \
    shaders.qrc 


