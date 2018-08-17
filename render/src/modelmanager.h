#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QVariant>

class ModelManager
{
public:
    ModelManager(const QString& jsonPath);

    ~ModelManager();

    QList<QVariant> models() const;

    void setModels(QVariant);

    void save();

private:
    QVariant data;
    QString m_jsonPath;
};


#endif // MODELMANAGER_H
