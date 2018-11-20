#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userview.h"
#include "connection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(processPendingDatagram()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    Userview viewer;
    viewer.exec();
}

//void MainWindow::on_logoutBtn_clicked()
//{
//    extern Log loger;
//    if(loger.freeConnection())
//        QMessageBox::warning(this, tr("注销"),tr("您已成功下线。"),QMessageBox::Yes);
//}

void MainWindow::on_testBtn_clicked()
{
    QByteArray datagram = "hello world!";
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
}

void MainWindow::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())  //拥有等待的数据报
        {
           QByteArray datagram; //拥于存放接收的数据报
    //让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
           datagram.resize(receiver->pendingDatagramSize());
           //接收数据报，将其存放到datagram中
           receiver->readDatagram(datagram.data(),datagram.size());
           //将数据报内容显示出来
           ui->msgReceiver->setText(datagram);
        }
}
