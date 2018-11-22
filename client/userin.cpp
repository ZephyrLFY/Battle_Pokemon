#include "userin.h"
#include "ui_userin.h"
#include "udpreceiver.h"

UserIn::UserIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserIn)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(dealDatagram()));
}

UserIn::~UserIn()
{
    delete ui;
}

void UserIn::dealDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       QString flag(datagram);
       tOrF = flag.toInt();
       qDebug() << flag << endl;
       qDebug() << "0" << endl;
    }

}

void UserIn::on_loginBtn_clicked()
{
    QString msg = "1";
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
    sleep(1);
    sender->writeDatagram(ui->usrLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    sender->writeDatagram(ui->pwdLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    qDebug() << tOrF << endl;
    receiver->waitForReadyRead();
    dealDatagram();
    qDebug() << tOrF << endl;

    if(tOrF == 1)
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("不存在该用户"),
                    QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
    else if(tOrF == 0)
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("密码错误！"),
                    QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
    }
    else
        accept();
}
