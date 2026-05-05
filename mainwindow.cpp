#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_jsondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flagButton = true;
    formatter = new jsonFormater(this);

    setWindowTitle("Клиент");

    client = new Client();
    Udp_Client = new UdpClient();

//    connect(client, SIGNAL(connectedToServer()), this, SLOT(showConnectedStatus()));
//    connect(client, SIGNAL(disconnectedFromServer()), this, SLOT(showDisconnectedStatus()));
    connect(client, SIGNAL(messageReceived(QString)), this, SLOT(printMessage(const QString)));
    connect(Udp_Client, SIGNAL(messageReceived(QString)), this, SLOT(printMessage(QString)));

    ui->listMessage->setLineWrapMode(QTextEdit::NoWrap);
    ui->listMessage->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete formatter;
    // delete jsonDialog;
}


void MainWindow::on_pushMessage_clicked()
{
    if (ui->textFieldMessage->text().isEmpty()) {
        return;
    }

    QString message = "(Client)-> ";
    message.append(ui->textFieldMessage->text().trimmed());
//    ui->listMessage->append(message);
    client->sendMessage(message);
    Udp_Client->sendMessage("UDP" + message);
    message.clear();
    ui->textFieldMessage->clear();
}


void MainWindow::on_buttonConnect_clicked()
{
    ui->listMessage->append("Подключение...");
    client->connectToServer();

    if (client->getConnectedToServer() && flagButton) {
        showConnectedStatus();
        flagButton = false;
    }else{
        flagButton = true;
        showDisconnectedStatus();
    }
}

void MainWindow::showConnectedStatus(){
    ui->listMessage->append("Соединение установлено!");
    ui->buttonConnect->setText("Disconect");
    ui->buttonPushJSON->setEnabled(true);
    ui->pushMessage->setEnabled(true);
    ui->textFieldMessage->setEnabled(true);
}

void MainWindow::showDisconnectedStatus(){
    ui->listMessage->append("Соединение разорвано(((");
    ui->buttonConnect->setText("Connect");
    ui->buttonPushJSON->setEnabled(false);
    ui->pushMessage->setEnabled(true);
    ui->textFieldMessage->setEnabled(true);
    client->desconnectToServer();
}

void MainWindow::printMessage(const QString &message){
    ui->listMessage->append(message);
}

void MainWindow::on_buttonPushJSON_clicked()
{
    auto jsonDialog = new JSONDialog(this);
    // jsonDialog->setAttribute(Qt::WA_DeleteOnClose);

//    connect(jsonDialog, &JSONDialog::dataRead, formatter, &jsonFormater::onFromData, Qt::UniqueConnection);
//    connect(formatter, &jsonFormater::jsonRead, client, &Client::onSendJson, Qt::UniqueConnection);

//    jsonDialog->show();

    auto resExec = jsonDialog->exec();
    if (resExec == 1) {
        jsonDialog->result();
        QString name, lastName, MidName;
        jsonDialog->getDataRead(name, lastName, MidName);
        QByteArray jsonData = formatter->onFromData(name, lastName, MidName);
        client->onSendJson(jsonData);
    }

    jsonDialog->deleteLater();

//    jsonDialog.exec();
}


void MainWindow::on_pushTxtForUDP_clicked()
{
    Udp_Client->sendFileUDP("/home/vitya/Загрузки/text.txt");
}

