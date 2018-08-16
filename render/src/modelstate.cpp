#include "modelgeometry.h"
#include "modelstate.h"
#include <QMetaObject>
#include <QMetaProperty>

ModelState::ModelState(QString texturePath):texturePath(texturePath),linearSpeed(0.0)
{
    Q_ASSERT(texturePath.length());
}

ModelState::ModelState(QVariant savedState)
{
    if (!savedState.isValid() || savedState.isNull() || !savedState.canConvert(QMetaType::QVariantMap))
    {
        qDebug() << "savedState is incorrect";
        return;
    }

    QVariantMap map = savedState.toMap();

    QString texturePath = map.value("texturePath").toString();

    if (texturePath.length()<=0){
        qDebug() << "texturePath is incorrect";
        return;
    }

    for(auto k:map.keys())
        setProperty(k.toLatin1(),map.value(k));

}

QVariant ModelState::toSavedState() const
{
    QVariantMap res;

    const QMetaObject * metaobject = metaObject();

    for (int i=0; i<metaobject->propertyCount(); ++i)
    {
        const QMetaProperty metaproperty = metaobject->property(i);
        res.insert(metaproperty.name(), property(metaproperty.name()).toString());
    }

    return res;
}

//qreal ModelState::linearSpeed() const
//{
//    return linearSpeed;
//}

//void ModelState::setLinearSpeed(qreal v)
//{

//}

//QVector3D ModelState::linearMove() const
//{

//}

//void ModelState::setLinearMove(const QVector3D &move)
//{

//}

//QVector3D ModelState::currPos() const
//{

//}

//void ModelState::setCurrPos(const QVector3D &pos)
//{

//}

//QVector3D ModelState::color() const
//{

//}

//void ModelState::setColor(const QVector3D &col)
//{

//}

//QString ModelState::modelPath() const
//{

//}

//void ModelState::setModelPath(const QString &mPath)
//{

//}

//bool ModelState::modelNormalized() const
//{

//}


//void ModelState::setModelNormalized(bool n)
//{
//    modelNormalized = n;
//}

//QString ModelState::texturePath() const
//{

//}

//void ModelState::setTexturePath(const QString &tPath)
//{

//}

//QString ModelState::id() const
//{

//}

//void ModelState::setId(QString i)
//{

//}
