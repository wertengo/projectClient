#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QDataStream>
#include <QDebug>
#include <QFile>

class UdpClient : public QObject
{
Q_OBJECT
public:
    UdpClient();
    ~UdpClient();

    void sendMessage(QString message);
    void sendFileUDP(const QString &filePath);

signals:
    void messageReceived(QString message);

private:
    QUdpSocket* m_pudp;

private slots:
    void slotProcessDatagrams();
};

#endif // UDPCLIENT_H
