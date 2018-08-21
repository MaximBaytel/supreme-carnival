#ifndef SCENESTATE_H
#define SCENESTATE_H

#include <QObject>
#include <QMatrix4x4>
#include "modelstate.h"

class SceneState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int logicalWidth MEMBER logicalWidth)
    Q_PROPERTY(int logicalHeight MEMBER logicalHeight)
    Q_PROPERTY(int logicalDepth MEMBER logicalDepth)

    Q_PROPERTY(QVector3D cameraPos MEMBER cameraPos)
    Q_PROPERTY(QMatrix4x4 projection MEMBER projection)

    Q_PROPERTY(QList<ModelState> models MEMBER models)

    Q_PROPERTY( QString id MEMBER id)

public:
    explicit SceneState(QObject *parent = nullptr);

private:
    int logicalWidth;
    int logicalHeight;
    int logicalDepth;

    QVector3D cameraPos;
    QMatrix4x4 projection;

    QList<ModelState> models;

    QString id;
};

#endif // SCENESTATE_H
