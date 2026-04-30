#include "client.h"

#include <QApplication>


Client::Client() : m_nNextBlockSize(0)
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

    tcpSocket->waitForConnected(3);

    qDebug() << "Состояние сокета: " << tcpSocket->state();

//    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
//        qDebug() << "INFO: Сокет подключен";
//        emit connectedToServer();
//    }else{
//        qDebug() << "INFO: Сокет не подключен";
//    }
}

void Client::desconnectToServer(){
    tcpSocket->disconnectFromHost();
//    tcpSocket->deleteLater();
}


bool Client::getConnectedToServer(){
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
            qDebug() << "INFO: Сокет подключен";
//            emit connectedToServer();
            return true;
        }

    qDebug() << "INFO: Сокет не подключен";

    return false;
}

// void Client::onSendJson(const QByteArray &arrayData){
//     if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
//         tcpSocket->write(arrayData);
//         tcpSocket->flush();
//         qDebug() << "Отправлен JSON файл серверу :) ";
//     }else{
//         qDebug() << "Ошибка сокет не подключен и JSON не был отправлен :(";
//     }
// }

void Client::onSendJson(const QByteArray &arrayData)
{
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Ошибка сокет не подключен и JSON не был отправлен :(";
        return;
    }

    // payload – чистый JSON, как есть (без 'T' и прочих префиксов)
    QByteArray payload = arrayData;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);          // версия должна совпадать с сервером
    out << (quint64)0;                             // резервируем 8 байт под размер
    out << payload;                                // пишем JSON-строку
    out.device()->seek(0);
    out << (quint64)(block.size() - sizeof(quint64)); // записываем реальный размер

    tcpSocket->write(block);
    tcpSocket->flush();
    qDebug() << "Отправлен JSON файл серверу :)";
}

// void Client::sendMessage(const QString &message){
//     if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
//        tcpSocket->write("T" + message.toUtf8());
//        tcpSocket->flush();
//     }
// }

void Client::sendMessage(const QString &message)
{
    if (tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray payload = ("T" + message).toUtf8();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint64)0;
    out << payload;
    out.device()->seek(0);
    out << (quint64)(block.size() - sizeof(quint64));

    tcpSocket->write(block);
    tcpSocket->flush();
}

// void Client::onReadyRead(){
//     QByteArray array = tcpSocket->readAll();
//     emit messageReceived(QString::fromUtf8(array));
// }

void Client::onReadyRead(){
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_0);

    for (;;) {
        if (!m_nNextBlockSize) {
            if (tcpSocket->bytesAvailable() < sizeof(quint64)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QByteArray array;
        in >> array;
        m_nNextBlockSize = 0;
        emit messageReceived(QString::fromUtf8(array));

    }

}

void Client::loadSettings(){
    // QString confPath = QDir::currentPath() + "/clientInit.ini";
    QString confPath = QString("%1/%2").arg(qApp->applicationDirPath()).arg("data");
    QDir dir(confPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QString filePath = confPath + "/clientInit.ini";
    QSettings settings(filePath, QSettings::IniFormat);

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
    qDebug() << "Размещение инит файла: " << confPath;
    qDebug() << "Вывод порта из инит файла: " << serverPort;
    qDebug() << "Вывод IP адреса из инит файла: " << serverIP;
}


Client::~Client(){
    tcpSocket->disconnectFromHost();
    tcpSocket->deleteLater();
}


