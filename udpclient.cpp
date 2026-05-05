#include "udpclient.h"

UdpClient::UdpClient()
{
    m_pudp = new QUdpSocket(this);
    m_pudp->bind(QHostAddress("172.16.202.129"), 2424);
    connect(m_pudp, SIGNAL(readyRead()), SLOT(slotProcessDatagrams()));
}

void UdpClient::slotProcessDatagrams()
{
    QByteArray baDatagram;

    do{
        baDatagram.resize(m_pudp->pendingDatagramSize());
        m_pudp->readDatagram(baDatagram.data(), baDatagram.size());
    }while(m_pudp->hasPendingDatagrams());

    // QDateTime dateTime;
    QByteArray dateTime;
    QDataStream in(&baDatagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_0);
    in >> dateTime;
    // QString text = QString::fromUtf8(dateTime);
    qDebug() << "Received: " + QString::fromUtf8(dateTime);
    emit messageReceived("Received: " + QString::fromUtf8(dateTime));
}

void UdpClient::sendMessage(QString message)
{
    QByteArray baDatagram;
    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (const char)0x01;
    out << message.toUtf8();
    qDebug() << message;
    emit messageReceived(message);

    m_pudp->writeDatagram(baDatagram, QHostAddress("172.16.202.129"), 2425);
}

void UdpClient::sendFileUDP(const QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Ошибка: не удалось открыть файл";
        return;
    }

    QUdpSocket udpSocket;
    const qint64 PAYLOAD_SIZE = 1024;
    quint32 sequenceNumber = 0;

    qDebug() << "Отправка файла размером: " << file.size() << " байт";

    while (!file.atEnd()) {
        QByteArray payload = QString(file.read(PAYLOAD_SIZE)).toUtf8();

        QByteArray datagram;
        QDataStream stream(&datagram, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_0);

        stream << (const char)0x02;
        stream << sequenceNumber;
        datagram.append(payload);

        qint64 bytesSent = m_pudp->writeDatagram(datagram, QHostAddress("172.16.202.129"), 2425);

        if (bytesSent == -1) {
            qDebug() << "Ошибка отправки";
        }
        sequenceNumber++;
    }

    qDebug() << "Файл отправлен всего пакетов: " << sequenceNumber;
    file.close();
}

UdpClient::~UdpClient()
{
    m_pudp->deleteLater();
}


