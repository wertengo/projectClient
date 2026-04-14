#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new Client();

    connect(client, SIGNAL(connectedToServer()), this, SLOT(showConnectedStatus()));
//    connect(client, SIGNAL(disconnectedFromServer()), this, SLOT(showDisconnectedStatus()));
    connect(client, SIGNAL(messageReceived(QString)), this, SLOT(printMessage(const QString)));

    ui->listMessage->setLineWrapMode(QTextEdit::NoWrap);
    ui->listMessage->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    message.clear();
    ui->textFieldMessage->clear();
}


void MainWindow::on_buttonConnect_clicked()
{
    ui->listMessage->append("Подключение...");
    client->connectToServer();
}

void MainWindow::showConnectedStatus(){
    ui->listMessage->append("Соединение установлено!");
}

void MainWindow::showDisconnectedStatus(){
    ui->listMessage->append("Соединение разорвано(((");
}

void MainWindow::printMessage(const QString &message){
    ui->listMessage->append(message);
}
