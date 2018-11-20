#include "newuser.h"
#include "ui_newuser.h"
#include "connection.h"

Newuser::Newuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newuser)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
}

Newuser::~Newuser()
{
    delete ui;
}

void Newuser::on_loginBtn_clicked()
{
    extern udpReceiver interact;
    interact.sendMsg(ui->usrLineEdit->text());
    interact.sendMsg(ui->pwdLineEdit->text());
    if(interact.updating())
        accept();
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("该用户名已被注册！"),
                           QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
