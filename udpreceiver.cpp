#include "udpreceiver.h"
#include "ui_udpreceiver.h"

udpReceiver::udpReceiver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udpReceiver)
{
    ui->setupUi(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(processPendingDatagram()));
    sender = new QUdpSocket(this);
}

udpReceiver::~udpReceiver()
{
    delete ui;
}

void udpReceiver::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())  //拥有等待的数据报
    {
       QByteArray datagram; //拥于存放接收的数据报
       //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
       datagram.resize(receiver->pendingDatagramSize());
       //接收数据报，将其存放到datagram中
       receiver->readDatagram(datagram.data(),datagram.size());
       QString flag(datagram);
       tOrF = flag.toInt();
       //将数据报内容显示出来
       ui->label->setText(datagram);
    }
}

int udpReceiver::updating()
{
    return tOrF;
}

void udpReceiver::whatToDo(int flag)
{
    QString sendMsg;
    if(flag == 1)
    {
        sendMsg = "1";
    }
    else if(flag == 2)
    {
        sendMsg = "2";
    }
    sender->writeDatagram(sendMsg.toUtf8(),QHostAddress::Broadcast,45454);
}

void udpReceiver::sendMsg(QString msg)
{
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
}

void udpReceiver::on_sendBtn_clicked()
{
    QString sendMsg = ui->sendLineEdit->text();
    sender->writeDatagram(sendMsg.toUtf8(),QHostAddress::Broadcast,45454);
}
