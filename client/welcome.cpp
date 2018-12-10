#include "welcome.h"
#include "ui_welcome.h"
#include "newuser.h"
#include "userin.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    initScene();
}

welcome::~welcome()
{
    delete scene;
    delete pix;
    delete ui;
}

void welcome::initScene()
{
    ui->textBrowser->viewport()->setAutoFillBackground(false);
    ui->textBrowser->setFrameStyle(QFrame::NoFrame);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0 , 0 , 600, 450);
    ui->background->setScene(scene);
    ui->background->setSceneRect(0, 0, ui->background->contentsRect().width(), ui->background->contentsRect().height());
    pix = new QPixmap(QPixmap::fromImage(QImage(":/new/ground/backGround/Back_welcome.jpeg")));
    *pix = pix->scaled(600,450);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(*pix);
    scene->addItem(item);
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
