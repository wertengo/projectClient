#ifndef JSONDIALOG_H
#define JSONDIALOG_H

#include <QDialog>
#include "jsonformater.h"

namespace Ui {
class JSONDialog;
}

class JSONDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JSONDialog(QWidget *parent = nullptr);
    ~JSONDialog();

    void getDataRead(QString &name, QString &lastName, QString &midName);

signals:
    void dataRead(QString &name, QString &lastName, QString &midName);

private slots:
    void on_pushButtonJson_clicked();

private:
    Ui::JSONDialog *ui;
};

#endif // JSONDIALOG_H
