#include "welcome.h"
#include "ui_welcome.h"
#include "newuser.h"
#include "userin.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_loginBtn_clicked()
{
    UserIn dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        accept();
    }
}

void welcome::on_logupBtn_clicked()
{
    Newuser dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        accept();
    }
}
