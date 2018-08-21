#ifndef MODELSTATE_H
#define MODELSTATE_H

#include <QObject> 
#include <QVector3D>

/*
linearSpeed - absolute value of velocity
linearMove  - vector of velocity
beginPos - position at beginning of the time
color - the color of the material (used without texture)
texturePath - the path to the texture file
modelPath - the path to the obj model file
*/

class ModelState: public QObject
{
	Q_OBJECT    
    Q_PROPERTY(qreal linearSpeed MEMBER linearSpeed)
    Q_PROPERTY(QVector3D linearMove MEMBER linearMove )
    Q_PROPERTY(QVector3D currPos MEMBER currPos)
    Q_PROPERTY(QVector3D color MEMBER color )
    Q_PROPERTY(QString modelPath MEMBER modelPath )
    Q_PROPERTY(bool modelNormalized MEMBER modelNormalized )
    Q_PROPERTY(QString texturePath MEMBER texturePath )
    Q_PROPERTY(bool hasTextureCoord MEMBER hasTextureCoord)
    Q_PROPERTY(QString id MEMBER id )

public:
	ModelState(QString texturePath);
	ModelState(QVariant savedState);

    QVariant toSavedState() const;

    friend bool operator == (const ModelState& l,const ModelState& r);

    ModelState(const ModelState& other);


    qreal linearSpeed;
    QVector3D linearMove;
    QVector3D currPos;
    QVector3D color;
    QString modelPath;
    bool modelNormalized;
    QString texturePath;
    QString id;
    bool hasTextureCoord;
};



#endif

