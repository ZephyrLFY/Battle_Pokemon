#include "pokeview.h"
#include "ui_pokeview.h"
#include "wideuse.h"

pokeView::pokeView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pokeView)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    rcv1Port = rcvPort + 1000;
    while(!receiver->bind(rcv1Port,QUdpSocket::DontShareAddress))
        rcv1Port = rcv1Port + 2;
    sendPort = rcv1Port + 1;
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    getPoke();
}

pokeView::~pokeView()
{
    delete sender;
    delete receiver;
    delete ui;
}

void pokeView::getPoke()
{
    QList<QString> text;
    text << "6" << usrName;
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    processPendingDatagram();
}

void pokeView::updateTable(QList<QString> &pokeInfo)
{
    qint32 i = 0;
    qint32 rowNum = pokeInfo.count("line");
    pokeModel = new QStandardItemModel(this);
    pokeModel->setColumnCount(2);
    pokeModel->setRowCount(rowNum);
    pokeModel->setHeaderData(0,Qt::Horizontal,"精灵名");
    pokeModel->setHeaderData(1,Qt::Horizontal,"等级");
    for(qint32 row = 0; row < rowNum; row++)
    {
        for(qint32 col = 0; col < 2; col++)
        {
            if(pokeInfo.at(i) == "line")
                i++;
            QStandardItem *item = new QStandardItem(pokeInfo.at(i));
            pokeModel->setItem(row,col,item);
            i++;
        }
    }
    ui->pokeInfo->setModel(pokeModel);
    ui->pokeInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pokeInfo->verticalHeader()->setVisible(false);
    ui->pokeInfo->resizeColumnsToContents();
    ui->pokeInfo->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->pokeInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void pokeView::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       QList<QString> pokeInfo;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       QDataStream stream(&datagram, QIODevice::ReadOnly);
       stream >> pokeInfo;
       updateTable(pokeInfo);
    }
}
