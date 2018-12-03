#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wideuse.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
}

MainWindow::~MainWindow()
{
    if(state)
        loseLink();
    delete sender;
    delete receiver;
    delete ui;
}

void MainWindow::loseLink()
{
    QList<QString> text;
    text << "4" << usrName;
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
}

void MainWindow::on_logoutBtn_clicked()
{
    loseLink();
    receiver->waitForReadyRead();
    if(state)
        QMessageBox::warning(this, tr("注销"),tr("您已成功下线。"),QMessageBox::Yes);
    state = 0;
}

void MainWindow::on_testBtn_clicked()
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

void MainWindow::updateUsr(QList<QString> &usrInfo)
{
    qint32 i = 0;
    qint32 rowNum = usrInfo.count("line");
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(13);
    model->setRowCount(rowNum);
    model->setHeaderData(0,Qt::Horizontal,"用户名");
    model->setHeaderData(1,Qt::Horizontal,"在线情况");
    model->setHeaderData(2,Qt::Horizontal,"胜率");
    model->setHeaderData(3,Qt::Horizontal,"数量徽章");
    model->setHeaderData(4,Qt::Horizontal,"精英徽章");
    model->setHeaderData(5,Qt::Horizontal,"精灵数量");
    model->setHeaderData(6,Qt::Horizontal,"小精灵1");
    model->setHeaderData(7,Qt::Horizontal,"小精灵2");
    model->setHeaderData(8,Qt::Horizontal,"小精灵3");
    model->setHeaderData(9,Qt::Horizontal,"小精灵4");
    model->setHeaderData(10,Qt::Horizontal,"小精灵5");
    model->setHeaderData(11,Qt::Horizontal,"小精灵6");
    model->setHeaderData(12,Qt::Horizontal,"小精灵7");
    for(qint32 row = 0; row < rowNum; row++)
    {
        for(qint32 col = 0; col < 12; col++)
        {
            if(usrInfo.at(i) == "line")
            {
                i++;
                break;
            }
            else if(col == 3 || col == 4)
                continue;
            else
            {
                QStandardItem *item = new QStandardItem(usrInfo.at(i));
                model->setItem(row,col,item);
                i++;
            }
        }
    }
    ui->userInfo->setModel(model);
    ui->userInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       QList<QString> usrInfo;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       ui->msgReceiver->setText(datagram);
       if(datagram.size() == 1)
           if(QString::fromUtf8(datagram) == "0")
               state = 0;
           else;
       else
           {
               QDataStream stream(&datagram, QIODevice::ReadWrite);
               stream >> usrInfo;
               updateUsr(usrInfo);
           }
    }
}
