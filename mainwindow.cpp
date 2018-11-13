#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userview.h"
#include "connection.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_logoutBtn_clicked()
{
    extern Log log;
    if(log.freeConnection())
        QMessageBox::warning(this, tr("注销"),tr("您已成功下线。"),QMessageBox::Yes);
}


