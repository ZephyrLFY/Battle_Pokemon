#include "udpreceiver.h"
#include "ui_udpreceiver.h"
#include <QDebug>

udpReceiver::udpReceiver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udpReceiver)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    sender = new QUdpSocket(this);
    receiver->bind(rcvPort,QUdpSocket::DontShareAddress);
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    loger = new Log;
    connect(receiver,SIGNAL(readyRead()),this,SLOT(dealDatagram()));
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
    sender->writeDatagram(sendMsg.toUtf8(),QHostAddress("10.8.162.229"),39962);
}

void udpReceiver::usrs(int inOrNew,QString name,QString pwd,QHostAddress address,quint16 hisPort)
{
    QByteArray sendgram;
    if(inOrNew == 1)
    {
        qint32 flag = userIn(name,pwd);
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
        if(newUsr(name,pwd))
            sendgram = "1";
        else        
            sendgram = "0";
    }
    sender->writeDatagram(sendgram,address,hisPort);
}


qint32 udpReceiver::userIn(QString name,QString pwd)
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

void udpReceiver::txShow(QString text)
{
    ui->label->setText(text);
}

void udpReceiver::linkOver(QString name,QHostAddress address,quint16 hisPort)
{
    loger->freeConnection(name);
    sender->writeDatagram("1",address,hisPort);
}

void udpReceiver::userInfo(QString name,QHostAddress address,quint16 hisPort)
{
    QByteArray temp;
    QList<QString> usrInfo = loger->getUsr();
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << usrInfo;
    sender->writeDatagram(temp,address,hisPort);
}

void udpReceiver::pokeInfo(QHostAddress address,quint16 hisPort)
{
    QByteArray temp;
    QList<QString> pokeInfo = loger->getPoke();
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << pokeInfo;
    sender->writeDatagram(temp,address,hisPort);
}

void udpReceiver::dealDatagram()
{
    QHostAddress *sendIp = new QHostAddress;
    quint16 *hisPort = new quint16;
    quint16 sendBack;
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        receiver->readDatagram(datagram.data(),datagram.size(),sendIp,hisPort);
        sendBack = *hisPort;
        sendBack = sendBack - 1;
        QList<QString> toDo;
        QDataStream stream(&datagram, QIODevice::ReadWrite);
        stream >> toDo;
        qint32 which = toDo.at(0).toInt();
        switch(which)
        {
        case 1:
        case 2:
        {
            usrs(which,toDo.at(1),toDo.at(2),*sendIp,sendBack);
            break;
        }
        case 3:
        {
            txShow(toDo.at(1));
            break;
        }
        case 4:
        {
            linkOver(toDo.at(1),*sendIp,sendBack);
            break;
        }
        case 5:
        {
            userInfo(toDo.at(1),*sendIp,sendBack);
            break;
        }
        case 6:
        {
            pokeInfo(*sendIp,sendBack);
            break;
        }
        }
    }
    delete sendIp;
}
