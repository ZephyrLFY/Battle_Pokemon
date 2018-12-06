#include "userview.h"
#include "ui_userview.h"
#include "wideuse.h"

userView::userView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userView)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(23232,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    getUsr();
}

userView::~userView()
{
    delete sender;
    delete receiver;
    delete ui;
}

void userView::getUsr()
{
    QList<QString> text;
    text << "5" << usrName;
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    processPendingDatagram();
}

void userView::updateTable(QList<QString> &usrInfo)
{
    qint32 i = 0;
    qint32 rowNum = usrInfo.count("line");
    bool color = false;
    usrModel = new QStandardItemModel(this);
    usrModel->setColumnCount(26);
    usrModel->setRowCount(rowNum);
    usrModel->setHeaderData(0,Qt::Horizontal,"用户名");
    usrModel->setHeaderData(1,Qt::Horizontal,"胜率");
    usrModel->setHeaderData(2,Qt::Horizontal,"数量徽章");
    usrModel->setHeaderData(3,Qt::Horizontal,"精英徽章");
    usrModel->setHeaderData(4,Qt::Horizontal,"精灵数量");
    usrModel->setHeaderData(5,Qt::Horizontal,"小精灵1");
    usrModel->setHeaderData(6,Qt::Horizontal,"等级1");
    usrModel->setHeaderData(7,Qt::Horizontal,"经验1");
    usrModel->setHeaderData(8,Qt::Horizontal,"小精灵2");
    usrModel->setHeaderData(9,Qt::Horizontal,"等级2");
    usrModel->setHeaderData(10,Qt::Horizontal,"经验2");
    usrModel->setHeaderData(11,Qt::Horizontal,"小精灵3");
    usrModel->setHeaderData(12,Qt::Horizontal,"等级3");
    usrModel->setHeaderData(13,Qt::Horizontal,"经验3");
    usrModel->setHeaderData(14,Qt::Horizontal,"小精灵4");
    usrModel->setHeaderData(15,Qt::Horizontal,"等级4");
    usrModel->setHeaderData(16,Qt::Horizontal,"经验4");
    usrModel->setHeaderData(17,Qt::Horizontal,"小精灵5");
    usrModel->setHeaderData(18,Qt::Horizontal,"等级5");
    usrModel->setHeaderData(19,Qt::Horizontal,"经验5");
    usrModel->setHeaderData(20,Qt::Horizontal,"小精灵6");
    usrModel->setHeaderData(21,Qt::Horizontal,"等级6");
    usrModel->setHeaderData(22,Qt::Horizontal,"经验6");
    usrModel->setHeaderData(23,Qt::Horizontal,"小精灵7");
    usrModel->setHeaderData(24,Qt::Horizontal,"等级7");
    usrModel->setHeaderData(25,Qt::Horizontal,"经验7");
    for(qint32 row = 0; row < rowNum; row++)
    {
        qint32 alive = i + 1;
        if(usrInfo.at(alive) == "1")
            color = true;
        for(qint32 col = 0; col < 25; col++)
        {
            if(usrInfo.at(i) == "line")
            {
                i++;
                break;
            }
            else if(col == 2)
            {
                qint32 num = usrInfo.at(i).toInt();
                QString badge = nullptr;
                if(num == 7)
                    badge = "Gold";
                else if(num > 4)
                    badge = "Silver";
                else if(num == 0)
                    badge = "None";
                else
                    badge = "Copper";
                QStandardItem *item = new QStandardItem(badge);
                usrModel->setItem(row,col,item);
            }
            else if(col == 3)
                continue;
            else
            {
                if(alive == i)//在线情况
                    i++;
                QStandardItem *item = new QStandardItem(usrInfo.at(i));
                if(i == alive - 1 && color)
                    item->setBackground(QBrush(QColor(153,0,153)));
                usrModel->setItem(row,col,item);
                i++;
            }
        }
        color = false;
    }
    ui->userInfo->setModel(usrModel);
    ui->userInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userInfo->verticalHeader()->setVisible(false);
    ui->userInfo->resizeColumnsToContents();
    ui->userInfo->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->userInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void userView::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       QList<QString> usrInfo;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       QDataStream stream(&datagram, QIODevice::ReadOnly);
       stream >> usrInfo;
       updateTable(usrInfo);
    }
}
