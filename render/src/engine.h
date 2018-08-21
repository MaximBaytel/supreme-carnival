#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QBasicTimer>
#include <QOpenGLWidget>
#include "modelgeometry.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QOpenGLWidget *glWidget = nullptr);

protected:
    void timerEvent(QTimerEvent *e) override;

    void updateScene();
    void drawScene();

private:
    void updateStep();



    QBasicTimer timer;

    QList<ModelGeomerty*> m_geometries;

    static const int m_frequency=50;

    QOpenGLWidget *mglWidget;

};

#endif // ENGINE_H
