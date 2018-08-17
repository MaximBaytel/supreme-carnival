#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "modelgeometry.h"
#include "modelmanager.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class ModelGeomerty;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    //void initShaders();
    //void initTextures();

private:
    QBasicTimer timer;
    //QOpenGLShaderProgram program;

    QList<ModelGeomerty*> m_geometries;

//    ModelGeomerty *geometries1;
//	ModelGeomerty *geometries2;

    //QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;

	
    QQuaternion rotation;

    ModelManager m_manager;
	
};

#endif // MAINWIDGET_H
