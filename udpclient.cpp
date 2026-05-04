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
    out << message.toUtf8();
    qDebug() << message;
    emit messageReceived(message);

    m_pudp->writeDatagram(baDatagram, QHostAddress("172.16.202.129"), 2425);
}

UdpClient::~UdpClient()
{
    m_pudp->deleteLater();
}


