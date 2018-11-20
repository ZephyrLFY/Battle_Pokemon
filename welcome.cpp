#include "welcome.h"
#include "ui_welcome.h"
#include "newuser.h"
#include "userin.h"
#include "udpreceiver.h"
#include <QDebug>

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_loginBtn_clicked()
{
    QString msg = "1";
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
    UserIn dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        accept();
    }
}

void welcome::on_logupBtn_clicked()
{
    QString msg = "2";
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
    Newuser dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        accept();
    }
}
