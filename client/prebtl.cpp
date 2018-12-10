#include "prebtl.h"
#include "ui_prebtl.h"
#include "wideuse.h"
#include "battleground.h"

preBtl::preBtl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preBtl)
{
    ui->setupUi(this);
    bindPort();
    getMy();
    getEnm();
    connect(ui->myPoke->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this,SLOT(getMyPoke(const QItemSelection&,const QItemSelection&)));
    connect(ui->enmPoke->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this,SLOT(getEnmPoke(const QItemSelection&,const QItemSelection&)));
}

preBtl::~preBtl()
{
    qint32 i = 0;
    qint32 j = 0;
    for(i = 0; i < rowNum1; i++)
        for(j = 0; j < 26; j++)
        {
            myPokeModel->clear();
        }
    delete myPokeModel;
    for(i = 0; i < rowNum2; i++)
        for(j = 0; j < 26; j++)
        {
            enmPokeModel->clear();
        }
    delete enmPokeModel;
    delete enmChose;
    delete ui;
    delete sender;
    delete receiver;
}

void preBtl::bindPort()
{
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    rcv1Port = rcvPort;
    while(!receiver->bind(rcv1Port,QUdpSocket::DontShareAddress))
        rcv1Port = rcv1Port + 2;
    sendPort = rcv1Port + 1;
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
}

void preBtl::getMy()
{
    QList<QString> text;
    text << "7" << localUser->getName();
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    processPendingDatagram();
}

void preBtl::getEnm()
{
    QList<QString> text;
    text << "6" << localUser->getName();
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    processPendingDatagram();
}

void preBtl::getMyPoke(const QItemSelection&,const QItemSelection&)
{
    which = ui->myPoke->currentIndex().row();
    myChosen = 1;
}

void preBtl::getEnmPoke(const QItemSelection&,const QItemSelection&)
{
    enmChose = new QList<QString>;
    qint32 row= ui->enmPoke->currentIndex().row();
    QModelIndex index = enmPokeModel->index(row,0);
    enmChose->append(enmPokeModel->data(index).toString());
    index = enmPokeModel->index(row,1);
    enmChose->append(enmPokeModel->data(index).toString());
    enmChose->append("0");
    enmChosen = 1;
}

void preBtl::myTable(QList<QString> &poke)
{
    qint32 i = 0;
    rowNum1 = poke.count("line");
    myPokeModel = new QStandardItemModel(this);
    myPokeModel->setColumnCount(3);
    myPokeModel->setRowCount(rowNum1);
    myPokeModel->setHeaderData(0,Qt::Horizontal,"精灵名");
    myPokeModel->setHeaderData(1,Qt::Horizontal,"等级");
    myPokeModel->setHeaderData(2,Qt::Horizontal,"经验");
    for(qint32 row = 0; row < rowNum1; row++)
    {
        for(qint32 col = 0; col < 3; col++)
        {
            if(poke.at(i) == "line")
                i++;
            QStandardItem *item = new QStandardItem(poke.at(i));
            myPokeModel->setItem(row,col,item);
            i++;
        }
    }
    ui->myPoke->setModel(myPokeModel);
    ui->myPoke->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->myPoke->verticalHeader()->setVisible(false);
    ui->myPoke->resizeColumnsToContents();
    ui->myPoke->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->myPoke->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void preBtl::enmTable(QList<QString> &poke)
{
    qint32 i = 0;
    rowNum2 = poke.count("line");
    enmPokeModel = new QStandardItemModel(this);
    enmPokeModel->setColumnCount(2);
    enmPokeModel->setRowCount(rowNum2);
    enmPokeModel->setHeaderData(0,Qt::Horizontal,"精灵名");
    enmPokeModel->setHeaderData(1,Qt::Horizontal,"等级");
    for(qint32 row = 0; row < rowNum2; row++)
    {
        for(qint32 col = 0; col < 2; col++)
        {
            if(poke.at(i) == "line")
                i++;
            QStandardItem *item = new QStandardItem(poke.at(i));
            enmPokeModel->setItem(row,col,item);
            i++;
        }
    }
    ui->enmPoke->setModel(enmPokeModel);
    ui->enmPoke->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->enmPoke->verticalHeader()->setVisible(false);
    ui->enmPoke->resizeColumnsToContents();
    ui->enmPoke->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->enmPoke->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void preBtl::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       QList<QString> Poke;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       QDataStream stream(&datagram, QIODevice::ReadOnly);
       stream >> Poke;
       qint32 temp = Poke.at(0).toInt();
       if(temp)
       {
           Poke.removeFirst();
           Poke.removeFirst();
           myTable(Poke);
       }
       else
           enmTable(Poke);
    }
}

void preBtl::on_buttonBox_accepted()
{
    if(!myChosen)
        QMessageBox::warning(this, tr("警告！"),tr("请选择您的精灵"),QMessageBox::Yes);
    else if(!enmChosen)
        QMessageBox::warning(this, tr("警告！"),tr("请选择要对战的精灵"),QMessageBox::Yes);
    else
    {
        localUser->choseToBattle(which);
        localUser->createEnm(*enmChose);
        accept();
    }
}
