#ifndef JSONFORMATER_H
#define JSONFORMATER_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class jsonFormater : public QObject
{
    Q_OBJECT
public:
    explicit jsonFormater(QObject *parent = nullptr);
    QByteArray onFromData(const QString &name, const QString &lastName, const QString &midName);


public slots:
//    void onFromData(const QString &name, const QString &lastName, const QString &midName);

signals:
    void jsonRead(const QByteArray &jsonData);

private:

};

#endif // JSONFORMATER_H
