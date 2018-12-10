#include "userview.h"
#include "ui_userview.h"
#include "wideuse.h"

userView::userView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userView)
{
    ui->setupUi(this);
    bindPort();
    getUsr();
}

userView::~userView()
{
    usrModel->clear();
    delete usrModel;
    delete sender;
    delete receiver;
    delete ui;
}

void userView::bindPort()
{
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    rcv1Port = rcvPort + 1000;
    while(!receiver->bind(rcv1Port,QUdpSocket::DontShareAddress))
        rcv1Port = rcv1Port + 2;
    sendPort = rcv1Port + 1;
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
}

void userView::getUsr()
{
    QList<QString> text;
    text << "5" << localUser->getName();
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
    rowNum = usrInfo.count("line");
    bool color = false;
    bool isMe = false;
    usrModel = new QStandardItemModel(this);
    usrModel->setColumnCount(27);
    usrModel->setRowCount(rowNum);
    usrModel->setHeaderData(0,Qt::Horizontal,"用户名");
    usrModel->setHeaderData(1,Qt::Horizontal,"胜场");
    usrModel->setHeaderData(2,Qt::Horizontal,"总场数");
    usrModel->setHeaderData(3,Qt::Horizontal,"数量徽章");
    usrModel->setHeaderData(4,Qt::Horizontal,"精英徽章");
    usrModel->setHeaderData(5,Qt::Horizontal,"精灵数量");
    usrModel->setHeaderData(6,Qt::Horizontal,"小精灵1");
    usrModel->setHeaderData(7,Qt::Horizontal,"等级1");
    usrModel->setHeaderData(8,Qt::Horizontal,"经验1");
    usrModel->setHeaderData(9,Qt::Horizontal,"小精灵2");
    usrModel->setHeaderData(10,Qt::Horizontal,"等级2");
    usrModel->setHeaderData(11,Qt::Horizontal,"经验2");
    usrModel->setHeaderData(12,Qt::Horizontal,"小精灵3");
    usrModel->setHeaderData(13,Qt::Horizontal,"等级3");
    usrModel->setHeaderData(14,Qt::Horizontal,"经验3");
    usrModel->setHeaderData(15,Qt::Horizontal,"小精灵4");
    usrModel->setHeaderData(16,Qt::Horizontal,"等级4");
    usrModel->setHeaderData(17,Qt::Horizontal,"经验4");
    usrModel->setHeaderData(18,Qt::Horizontal,"小精灵5");
    usrModel->setHeaderData(19,Qt::Horizontal,"等级5");
    usrModel->setHeaderData(20,Qt::Horizontal,"经验5");
    usrModel->setHeaderData(21,Qt::Horizontal,"小精灵6");
    usrModel->setHeaderData(22,Qt::Horizontal,"等级6");
    usrModel->setHeaderData(23,Qt::Horizontal,"经验6");
    usrModel->setHeaderData(24,Qt::Horizontal,"小精灵7");
    usrModel->setHeaderData(25,Qt::Horizontal,"等级7");
    usrModel->setHeaderData(26,Qt::Horizontal,"经验7");
    for(qint32 row = 0; row < rowNum; row++)
    {
        qint32 alive = i + 1;
        if(usrInfo.at(alive) == "1")
            color = true;
        if(usrInfo.at(i) == localUser->getName())
        {
            isMe = true;
            color = false;
        }
        for(qint32 col = 0; col < 26; col++)
        {
            if(usrInfo.at(i) == "line")
            {
                i++;
                break;
            }
            else if(col == 3)
            {
                QString badge = localUser->getNumBadge();
                QStandardItem *item = new QStandardItem(badge);
                switch(localUser->getNumColor())
                {
                case 3:
                    item->setBackground(QBrush(QColor(255,215,0)));
                    break;
                case 2:
                    item->setBackground(QBrush(QColor(192,192,192)));
                    break;
                case 1:
                    item->setBackground(QBrush(QColor(196,112,34)));
                    break;
                default:
                    break;
                }
                usrModel->setItem(row,col,item);
            }
            else if(col == 4)
            {
                QString badge = localUser->getHighBadge();
                QStandardItem *item = new QStandardItem(badge);
                switch(localUser->getHighColor())
                {
                case 3:
                    item->setBackground(QBrush(QColor(255,215,0)));
                    break;
                case 2:
                    item->setBackground(QBrush(QColor(192,192,192)));
                    break;
                case 1:
                    item->setBackground(QBrush(QColor(196,112,34)));
                    break;
                default:
                    break;
                }
                usrModel->setItem(row,col,item);
            }
            else
            {
                if(alive == i)//在线情况
                    i++;
                QStandardItem *item = new QStandardItem(usrInfo.at(i));
                if(i == alive - 1)
                {
                    if(color)
                        item->setBackground(QBrush(QColor(153,0,153)));
                    else if(isMe)
                        item->setBackground(QBrush(QColor(162,205,90)));
                }
                usrModel->setItem(row,col,item);
                i++;
            }
        }
        color = false;
        isMe = false;
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
