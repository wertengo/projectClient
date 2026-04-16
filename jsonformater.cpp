#include "jsonformater.h"

jsonFormater::jsonFormater(QObject *parent)
{

}

QByteArray jsonFormater::onFromData(const QString &name, const QString &lastName, const QString &midName){
    QJsonObject objectData;
    objectData["name"] = name;
    objectData["lastName"] = lastName;
    objectData["midName"] = midName;

    QJsonDocument doc(objectData);
    QByteArray arrayData = doc.toJson(QJsonDocument::Compact);

    qDebug() << "Есть json данные: " << arrayData;
    return arrayData;
//    emit jsonRead(arrayData);
}


