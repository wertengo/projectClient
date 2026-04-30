#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDir>
#include <QSettings>
#include <QDataStream>


class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();

    void sendMessage(const QString &message);
    void connectToServer();
    void desconnectToServer();
    bool getConnectedToServer();


signals:
    void connectedToServer();
//    void disconnectedFromServer();
    void messageReceived(QString message);
public slots:
    void onSendJson(const QByteArray &arrayData);

private slots:
    void onReadyRead();
//    void connectedToServer();

private:
    quint64 m_nNextBlockSize;
    QTcpSocket *tcpSocket;
    QList<QByteArray> message;
    QString serverIP;
    quint16 serverPort;
    void loadSettings();
};

#endif // CLIENT_H
