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
    //Q_PROPERTY(QVector3D linearMove READ linearMove WRITE setLinearMove)
    //Q_PROPERTY(QVector3D currPos READ currPos WRITE setCurrPos)
    //Q_PROPERTY(QVector3D color READ color WRITE setColor)
    //Q_PROPERTY(QString modelPath READ modelPath WRITE setModelPath)
    //Q_PROPERTY(bool modelNormalized READ modelNormalized WRITE setModelNormalized)
    //Q_PROPERTY(QString texturePath READ texturePath WRITE setTexturePath)
    //Q_PROPERTY(QString id READ id WRITE setId)

    Q_PROPERTY(QVector3D linearMove MEMBER linearMove )
    Q_PROPERTY(QVector3D currPos MEMBER currPos)
    Q_PROPERTY(QVector3D color MEMBER color )
    Q_PROPERTY(QString modelPath MEMBER modelPath )
    Q_PROPERTY(bool modelNormalized MEMBER modelNormalized )
    Q_PROPERTY(QString texturePath MEMBER texturePath )
    Q_PROPERTY(QString id MEMBER id )


public:
	ModelState(QString texturePath);

	ModelState(QVariant savedState);

    QVariant toSavedState() const;

//	qreal linearSpeed() const;
//	void setLinearSpeed(qreal v);

//    QVector3D linearMove() const;
//    void setLinearMove(const QVector3D& move);

//    QVector3D currPos() const;
//    void setCurrPos(const QVector3D& pos);

//    QVector3D color() const;
//    void setColor(const QVector3D& col);

//    QString modelPath() const;
//    void setModelPath(const QString& mPath);

//    bool modelNormalized() const;
//    void setModelNormalized(bool n);

//    QString texturePath() const;
//    void setTexturePath(const QString& tPath);

//    QString id() const;
//    void setId(QString i);

    qreal linearSpeed;
    QVector3D linearMove;
    QVector3D currPos;
    QVector3D color;
    QString modelPath;
    bool modelNormalized;
    QString texturePath;
    QString id;
	
};


#endif

