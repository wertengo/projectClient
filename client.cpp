#include "client.h"

Client::Client()
{
    tcpSocket = new QTcpSocket(this);

    loadSettings();

//    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectedToServer()));
//    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectedToServer()));
//    connect(tcpSocket, SIGNAL(disconected()), this, SLOT(disconnectedFromServer()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

}

void Client::connectToServer(){
    tcpSocket->connectToHost(serverIP, serverPort);

    qDebug() << "Состояние сокета: " << tcpSocket->state();
    tcpSocket->waitForConnected(300);

    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "INFO: Сокет подключен";
        emit connectedToServer();
    }else{
        qDebug() << "INFO: Сокет не подключен";
    }
}

void Client::sendMessage(const QString &message){
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
       tcpSocket->write(message.toUtf8());
       tcpSocket->flush();
    }
}

void Client::onReadyRead(){
    QByteArray array = tcpSocket->readAll();
    emit messageReceived(QString::fromUtf8(array));
}

void Client::loadSettings(){
    QString confPath = QDir::currentPath() + "/clientInit.ini";
    QSettings settings(confPath, QSettings::IniFormat);

    if (!settings.contains("Server/Port")) {
        settings.setValue("Server/Port", 56789);
        settings.sync();
        qDebug() << "ini файл должен создаться по этому пути: " << confPath;
    }

    if (!settings.contains("Server/IP")) {
        settings.setValue("Server/IP", "192.168.1.7");
        settings.sync();
    }

    serverPort = settings.value("Server/Port").toInt();
    serverIP = settings.value("Server/IP").toString();
    qDebug() << "Вывод порта из инит файла: " << serverPort;
    qDebug() << "Вывод IP адреса из инит файла: " << serverIP;
}


Client::~Client(){
    tcpSocket->disconnectFromHost();
}


