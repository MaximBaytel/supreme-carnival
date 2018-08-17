#include "modelmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

ModelManager::ModelManager(const QString &jsonPath):m_jsonPath(jsonPath)
{
    QFile f(jsonPath);

    if (!f.open(QIODevice::ReadOnly)){
        qDebug() << "can't open json file";
        return;
    }

    QByteArray binData = f.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(binData);

    data = doc.toVariant();
}

ModelManager::~ModelManager()
{
    save();
}

QList<QVariant> ModelManager::models() const
{
    return data.toList();
}

void ModelManager::setModels(QVariant dt)
{
    data = dt;
}

void ModelManager::save()
{
    QFile f(m_jsonPath);

    if (!f.open(QIODevice::WriteOnly)){
        qDebug() << "can't open json file";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromVariant(data);

    f.write(doc.toJson());
}
