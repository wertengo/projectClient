#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>
#include "udpclient.h"
#include "jsonformater.h"
#include "jsondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showConnectedStatus();
    void showDisconnectedStatus();
    ~MainWindow();

private slots:
    void on_pushMessage_clicked();
    void on_buttonConnect_clicked();

//    void showConnectedStatus();
//    void showDisconnectedStatus();
    void printMessage(const QString &message);
    void on_buttonPushJSON_clicked();

    void on_pushTxtForUDP_clicked();

private:
    Ui::MainWindow *ui;
    Client *client;
    UdpClient *Udp_Client;
    jsonFormater *formatter;
    bool flagButton;
    //JSONDialog *jsonDialog;
};
#endif // MAINWINDOW_H
