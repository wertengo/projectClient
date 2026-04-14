#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushMessage_clicked();
    void on_buttonConnect_clicked();

    void showConnectedStatus();
    void showDisconnectedStatus();
    void printMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    Client *client;
};
#endif // MAINWINDOW_H
