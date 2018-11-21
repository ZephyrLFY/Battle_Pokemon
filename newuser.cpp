#include "newuser.h"
#include "ui_newuser.h"
#include "connection.h"
#include "udpreceiver.h"
#include  <unistd.h>

Newuser::Newuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newuser)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(45454,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(dealDatagram()));
}

Newuser::~Newuser()
{
    delete ui;
}

void Newuser::dealDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       QString flag(datagram);
       this->flag = flag.toInt();
    }
}

void Newuser::on_loginBtn_clicked()
{
    QString msg = "2";
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
    sleep(1);
    sender->writeDatagram(ui->usrLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    sender->writeDatagram(ui->pwdLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    if(flag)
        accept();
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("该用户名已被注册！"),
                           QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
