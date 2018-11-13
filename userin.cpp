#include "userin.h"
#include "ui_userin.h"
#include "connection.h"
#include <QDebug>

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
    extern Log log;
    QSqlQuery query;
    QString name = ui->usrLineEdit->text();
    QString pwd = log.searchPwd(name);
    if(pwd == ui->pwdLineEdit->text())
    {
        query.prepare("update player set alive = ? where ID = ?");
        query.addBindValue(1);
        query.addBindValue(name);
        query.exec();
        accept();
    }
    else if(pwd == "NULL")
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("不存在该用户"),
                    QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                    tr("密码错误！"),
                    QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
    }
}
