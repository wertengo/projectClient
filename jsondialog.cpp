#include "jsondialog.h"
#include "ui_jsondialog.h"

#include "jsonformater.h"

JSONDialog::JSONDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JSONDialog)
{
    ui->setupUi(this);

}

JSONDialog::~JSONDialog()
{
    qDebug() << "~JSONDialog()";
    delete ui;
}

void JSONDialog::getDataRead(QString &name, QString &lastName, QString &midName)
{
    name = ui->nameLine->text();
    lastName = ui->lastNameLine->text();
    midName = ui->middleNameLine->text();
}

void JSONDialog::on_pushButtonJson_clicked()
{
//    QString name = ui->nameLine->text();
//    QString lastName = ui->lastNameLine->text();
//    QString midleName = ui->middleNameLine->text();
//    ui->nameLine->clear();
//    ui->lastNameLine->clear();
//    ui->middleNameLine->clear();

    //emit dataRead(name, lastName, midleName);
    accept();
}

