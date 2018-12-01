#include "udpreceiver.h"
#include "ui_udpreceiver.h"
#include <QDebug>
#include <unistd.h>

udpReceiver::udpReceiver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udpReceiver)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    receiver->bind(45454,QUdpSocket::ShareAddress);
    loger = new Log;
    connect(receiver,SIGNAL(readyRead()),this,SLOT(dealDatagram()));
    sender = new QUdpSocket(this);
}

udpReceiver::~udpReceiver()
{
    delete ui;
    delete receiver;
    delete sender;
}

void udpReceiver::on_sendBtn_clicked()
{
    QString sendMsg = ui->sendLineEdit->text();
    sender->writeDatagram(sendMsg.toUtf8(),QHostAddress("10.128.199.8"),39962);
}

void udpReceiver::usrs(int inOrNew)
{
    QByteArray datagram,sendgram;
    QString userName,userPwd;
    receiver->waitForReadyRead();
    datagram.resize(receiver->pendingDatagramSize());
    receiver->readDatagram(datagram.data(),datagram.size());
    userName = QString::fromUtf8(datagram);
    receiver->waitForReadyRead();
    datagram.resize(receiver->pendingDatagramSize());
    receiver->readDatagram(datagram.data(),datagram.size());
    userPwd = QString::fromUtf8(datagram);
    if(inOrNew == 1)
    {
        int flag = userIn(userName,userPwd);
        if(flag == 3)
            sendgram = "3";
        else if(flag == 2)
            sendgram = "2";
        else if(flag == 1)        
            sendgram = "1";
        else        
            sendgram = "0";
    }
    else
    {
        if(newUsr(userName,userPwd))        
            sendgram = "1";
        else        
            sendgram = "0";
    }
    sender->writeDatagram(sendgram,QHostAddress("10.128.199.8"),39962);
}


int udpReceiver::userIn(QString name,QString pwd)
{
    QString usrPwd = loger->searchPwd(name);
    if(pwd == usrPwd)
    {
        if(loger->aliveOrNot(name))
            return 3;
        else
        {
            loger->linkStart(name);
            return 2;
        }
    }
    else if(usrPwd == "NULL")
    {
        return 1;
    }
    return 0;
}

bool udpReceiver::newUsr(QString name,QString pwd)
{
    if(loger->addNewusr(name,pwd))
    {
        loger->addPokemon(name);
        return true;
    }
    return false;
}

void udpReceiver::txShow()
{
    QByteArray datagram;
    datagram.resize(receiver->pendingDatagramSize());
    receiver->readDatagram(datagram.data(),datagram.size());
    ui->label->setText(datagram);
}

void udpReceiver::linkOver()
{
    QByteArray datagram;
    datagram.resize(receiver->pendingDatagramSize());
    receiver->readDatagram(datagram.data(),datagram.size());
    QString name = datagram.data();
    loger->freeConnection(name);
    sender->writeDatagram("1",QHostAddress("10.128.199.8"),39962);
}

void udpReceiver::dealDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size());
        QString dataKind(datagram);
        int which = datagram.toInt();
        switch(which)
        {
        case 1:
        case 2:
        {
            usrs(which);
            break;
        }
        case 3:
        {
            txShow();
            break;
        }
        case 4:
        {
            linkOver();
            break;
        }
        }
    }
}
