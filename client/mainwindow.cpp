#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wideuse.h"
#include "logout.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    on_usrBtn_clicked();
    connect(ui->userInfo->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this,SLOT(getUsrInfo(const QItemSelection&,const QItemSelection&)));
    on_pokeBtn_clicked();
    connect(ui->pokeInfo->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this,SLOT(getPokeInfo(const QItemSelection&,const QItemSelection&)));
}

MainWindow::~MainWindow()
{
    if(state)
        loseLink();
    delete sender;
    delete receiver;
    delete ui;
}

void MainWindow::getUsrInfo(const QItemSelection&,const QItemSelection&)
{
    QModelIndex temp = ui->userInfo->selectionModel()->currentIndex();
    QVariant what = usrModel->data(temp);
    myPoke = what.toString();
}

void MainWindow::getPokeInfo(const QItemSelection&,const QItemSelection&)
{
    QModelIndex temp = ui->pokeInfo->selectionModel()->currentIndex();
    QVariant what = pokeModel->data(temp);
    enmPoke = what.toString();
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
    logout sure;
    if(sure.exec() == QDialog::Accepted)
    {
        loseLink();
        receiver->waitForReadyRead();
        processPendingDatagram();
        if(state == 0)
            QMessageBox::warning(this,"注销失败","请重试。",QMessageBox::Yes);
        else
            this->close();
    }
}

void MainWindow::on_usrBtn_clicked()
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

void MainWindow::on_pokeBtn_clicked()
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

void MainWindow::updateUsr(QList<QString> &usrInfo)
{
    qint32 i = 0;
    qint32 rowNum = usrInfo.count("line");
    bool color = false;
    usrModel = new QStandardItemModel(this);
    usrModel->setColumnCount(12);
    usrModel->setRowCount(rowNum);
    usrModel->setHeaderData(0,Qt::Horizontal,"用户名");
    usrModel->setHeaderData(1,Qt::Horizontal,"胜率");
    usrModel->setHeaderData(2,Qt::Horizontal,"数量徽章");
    usrModel->setHeaderData(3,Qt::Horizontal,"精英徽章");
    usrModel->setHeaderData(4,Qt::Horizontal,"精灵数量");
    usrModel->setHeaderData(5,Qt::Horizontal,"小精灵1");
    usrModel->setHeaderData(6,Qt::Horizontal,"小精灵2");
    usrModel->setHeaderData(7,Qt::Horizontal,"小精灵3");
    usrModel->setHeaderData(8,Qt::Horizontal,"小精灵4");
    usrModel->setHeaderData(9,Qt::Horizontal,"小精灵5");
    usrModel->setHeaderData(10,Qt::Horizontal,"小精灵6");
    usrModel->setHeaderData(11,Qt::Horizontal,"小精灵7");
    for(qint32 row = 0; row < rowNum; row++)
    {
        qint32 alive = i + 1;
        if(usrInfo.at(alive) == "1")
            color = true;
        for(qint32 col = 0; col < 11; col++)
        {
            if(usrInfo.at(i) == "line")//换行
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

void MainWindow::updatePoke(QList<QString> &pokeInfo)
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

void MainWindow::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       QList<QString> infoM;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       ui->msgReceiver->setText(datagram);
       if(datagram.size() == 1)
           if(QString::fromUtf8(datagram) == "0")
               state = 0;
           else;
       else
           {
               QDataStream stream(&datagram, QIODevice::ReadOnly);
               stream >> infoM;
               qint32 temp = infoM.at(0).toInt();
               infoM.removeFirst();
               if(temp)
               {
                   updateUsr(infoM);
               }
               else
               {
                   updatePoke(infoM);
               }
           }
    }
}

void MainWindow::on_lvlBtn_clicked()
{
    //QusrModelIndex index = ui->pokeInfo->currentIndex();
    //QVariant data = ui->pokeInfo->
    //QStandardItem *which = new QStandardItem(index);
}
