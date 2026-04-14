#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDir>
#include <QSettings>


class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();

    void sendMessage(const QString &message);
    void connectToServer();


signals:
    void connectedToServer();
//    void disconnectedFromServer();
    void messageReceived(QString message);
public slots:


private slots:
    void onReadyRead();
//    void connectedToServer();

private:
    QTcpSocket *tcpSocket;
    QList<QByteArray> message;
    QString serverIP;
    quint16 serverPort;
    void loadSettings();
};

#endif // CLIENT_H
