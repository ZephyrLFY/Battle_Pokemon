#include "newuser.h"
#include "ui_newuser.h"
#include "wideuse.h"

Newuser::Newuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newuser)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
    bindPort();
}

Newuser::~Newuser()
{
    delete sender;
    delete receiver;
    delete ui;
}

void Newuser::bindPort()
{
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    rcv1Port = rcvPort;
    while(!receiver->bind(rcv1Port,QUdpSocket::DontShareAddress))
        rcv1Port = rcv1Port + 2;
    sendPort = rcv1Port + 1;
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(dealDatagram()));
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
    QList<QString> login;
    login << "2" << ui->usrLineEdit->text().toUtf8() << ui->pwdLineEdit->text().toUtf8();
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << login;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    dealDatagram();
    if(flag)
    {
        QString usrName = ui->usrLineEdit->text().toUtf8();
        localUser = new localUsr(usrName);
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),tr("该用户名已被注册！"),QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
