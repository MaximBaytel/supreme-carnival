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

    QString mPath = map.value("modelPath").toString();

    if (mPath.length()<=0){
        qDebug() << "texturePath is incorrect";
        return;
    }

    for(auto k:map.keys())
    {
        if (k == "linearMove" || k == "currPos" || k == "color"){
           QStringList list =  map.value(k).toString().split(",");
            setProperty(k.toLatin1(),QVector3D(list.value(0).toFloat(),list.value(1).toFloat(),list.value(2).toFloat()));
        }
        else
            setProperty(k.toLatin1(),map.value(k));
    }

}

QVariant ModelState::toSavedState() const
{
    QVariantMap res;

    const QMetaObject * metaobject = metaObject();

    for (int i=0; i<metaobject->propertyCount(); ++i)
    {
        const QMetaProperty metaproperty = metaobject->property(i);

        if (metaproperty.type() == QMetaType::QVector3D)
        {
            QVector3D temp = property(metaproperty.name()).value<QVector3D>();

            QString str = QString::asprintf("%f,%f,%f",temp.x(),temp.y(),temp.z());

            res.insert(metaproperty.name(),str);
        }

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
