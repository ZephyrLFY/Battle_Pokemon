#include "userin.h"
#include "ui_userin.h"
#include <QSqlQuery>

UserIn::UserIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserIn)
{
    ui->setupUi(this);
}

UserIn::~UserIn()
{
    delete ui;
}

void UserIn::on_loginBtn_clicked()
{
    extern udpReceiver interact;
    interact.sendMsg(ui->usrLineEdit->text());
    interact.sendMsg(ui->pwdLineEdit->text());
    if(interact.updating() == 1)
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("不存在该用户"),
                    QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
    else if(interact.updating() == 0)
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
