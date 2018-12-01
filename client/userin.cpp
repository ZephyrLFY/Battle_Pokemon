#include "userin.h"
#include "ui_userin.h"

UserIn::UserIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserIn)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(39962,QUdpSocket::ShareAddress);
}

UserIn::~UserIn()
{
    delete sender;
    delete receiver;
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
    }
}

void UserIn::on_loginBtn_clicked()
{
    QString msg = "1";
    sender->writeDatagram(msg.toUtf8(),QHostAddress::Broadcast,45454);
    sender->writeDatagram(ui->usrLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    sender->writeDatagram(ui->pwdLineEdit->text().toUtf8(),QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    dealDatagram();
    switch(tOrF)
    {
    case 3:
    case 1:
    {
        if(tOrF == 3)
            QMessageBox::warning(this, tr("警告！"),tr("该用户已上线"),QMessageBox::Yes);
        else
            QMessageBox::warning(this, tr("警告！"),tr("不存在该用户"),QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
        break;
    }
    case 0:
    {
        QMessageBox::warning(this, tr("警告！"),tr("密码错误！"),QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        break;
    }
    default:
    {
        extern QString usrName;
        usrName = ui->usrLineEdit->text().toUtf8();
        accept();
    }
    }
}
