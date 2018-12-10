#include "battleground.h"
#include "ui_battleground.h"
#include "wideuse.h"
#include "mymap.h"

BattleThread::BattleThread(pokemon *a,pokemon *b)
{
    this->a = a;
    this->b = b;
}

void BattleThread::run()
{
    battle(*a,*b);
    emit done();
}

void BattleThread::beat(pokemon &a,pokemon&b,int ran)//攻击函数，攻击者和被攻击者
{
    QString temp1,temp2;
    int rans = generateRandomInteger(1,100);
    a.getTimer();
    b.getTimer();
    if(a.getState() == 1)
            temp2 = "对方被眩晕了！无法攻击";
    else
    {
        if(rans > 85)
        {
            temp1 = a.skill();
            if(a.getType() == 4)
            {
                b.setState(1);
                b.setTimer(2);
            }
        }
        else
            temp1 = a.attack();

        if(a.getState() == 3)
        {
            if(b.getState() == 2)
                temp2 = b.damagedeal(a.damagecost());
            else
                temp2 = b.damagedeal(a.damagecost() + a.getLvl()*3);
        }
        else if(b.getState() == 2)
            temp2 = b.damagedeal(a.damagecost() - b.getLvl()*3);
        else
            temp2 = b.damagedeal(a.damagecost());
    }

    if(ran == 0)
    {
        emit EnmLabel(temp2);
        emit MyOutput(temp1);
    }
    else
    {
        emit MyLabel(temp2);
        emit EnmOutput(temp1);
    }
}

void BattleThread::result(pokemon &a,pokemon &b)
{
    if((!a.alive())&&(!b.alive()))
        qDebug() << "Both of them are dead." << endl;
    else if(a.alive())
    {
        qDebug() << "Congratulations! Your pet wins!" << endl;
        a.expup(b.gain());
        qDebug() << "You gain " << b.gain() << " exp." << endl;
        if(a.upornot())
            a.lvlup();
    }
    else
        qDebug() << "Sorry, your pet is dead." << endl;
}

void BattleThread::battle(pokemon &a,pokemon &b)/*根据时间以及攻击间隔，互相攻击*/
{
    clock_t a_delay = a.atkf() * CLOCKS_PER_SEC;
    clock_t b_delay = b.atkf() * CLOCKS_PER_SEC;
    clock_t a_start = clock();
    clock_t b_start = clock();
    while(a.alive()&&b.alive())
    {
        while((clock()-a_start < a_delay)&&(clock()-b_start < b_delay))
            ;
        if(clock() - a_start >= a_delay)
        {
            beat(a,b,0);
            a_start = clock();
        }
        if(clock()-b_start >= b_delay)
        {
            beat(b,a,123456);
            b_start = clock();
        }
    }
    result(a,b);
    a.hpfull();
    b.hpfull();
}

int BattleThread::generateRandomInteger(int min,int max)
{
    Q_ASSERT(min < max);
    // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
    // 每次启动程序，只添加一次种子，以做到数字真正随机。
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom = qrand() % (max - min);
    nRandom = min + nRandom;

    return nRandom;
}

Battleground::Battleground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Battleground)
{
    ui->setupUi(this);
    my = localUser->chosePoke();
    enm = localUser->getEnm();
    initMap();
    initPoke(my->getName(),enm->getName());
    update();
    thread = new BattleThread(my,enm);
    connects();
    ui->overBtn->setEnabled(0);
}

Battleground::~Battleground()
{
    delete ui;
    delete scene;
}

void Battleground::connects()
{
    connect(my,SIGNAL(fresh()),this,SLOT(update()));
    connect(enm,SIGNAL(fresh()),this,SLOT(update()));
    connect(thread,SIGNAL(done()), this, SLOT(over()));
    connect(thread, SIGNAL(MyLabel(QString)),ui->myInfo, SLOT(setText(QString)));
    connect(thread, SIGNAL(EnmLabel(QString)),ui->enmInfo, SLOT(setText(QString)));
    connect(thread, SIGNAL(MyOutput(QString)),ui->myOut, SLOT(setText(QString)));
    connect(thread, SIGNAL(EnmOutput(QString)),ui->enmOut, SLOT(setText(QString)));
}

void Battleground::update()
{
    ui->myHp->setValue(my->getHp());
    ui->enmHp->setValue(enm->getHp());
}

void Battleground::over()
{
    ui->overBtn->setEnabled(1);
    delete thread;
}

void Battleground::initScene()
{
    scene->setSceneRect(25 , 20 , 600, 400);
    ui->myOut->viewport()->setAutoFillBackground(false);
    ui->myOut->setFrameStyle(QFrame::NoFrame);
    ui->enmOut->viewport()->setAutoFillBackground(false);
    ui->enmOut->setFrameStyle(QFrame::NoFrame);
    ui->myInfo->viewport()->setAutoFillBackground(false);
    ui->myInfo->setFrameStyle(QFrame::NoFrame);
    ui->enmInfo->viewport()->setAutoFillBackground(false);
    ui->enmInfo->setFrameStyle(QFrame::NoFrame);
}

void Battleground::initMap()
{
    scene = new QGraphicsScene(this);
    initScene();
    ui->BattleView->setScene(scene);
    ui->BattleView->setSceneRect(0, 0, ui->BattleView->contentsRect().width(), ui->BattleView->contentsRect().height());
    if(localUser->getBattle())
        pix = new QPixmap(QPixmap::fromImage(QImage(":/new/ground/backGround/Back_lvlup.jpeg")));
    else
        pix = new QPixmap(QPixmap::fromImage(QImage(":/new/ground/backGround/Back_battle.jpeg")));
    *pix = pix->scaled(600,400);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(*pix);
    scene->addItem(item);
    scene->setFocus();
}

void Battleground::initPoke(QString nameL,QString nameR)
{
    qint32 i,j;
    if(nameL == "Hitmonlee")
        i = 1;
    else if(nameL == "Charmander")
        i = 2;
    else if(nameL == "Squirtle")
        i = 3;
    else if(nameL == "Licktung")
        i = 4;
    else if(nameL == "Muk")
        i = 5;
    else if(nameL == "Krabby")
        i = 6;
    else if(nameL == "Shellder")
        i = 7;
    else if(nameL == "Onix")
        i = 8;
    else if(nameL == "Geodude")
        i = 9;
    else if(nameL == "Bulbasaur")
        i = 10;
    else if(nameL == "Pidgeotto")
        i = 11;
    else
        i = 12;
    if(nameR == "Hitmonlee")
        j = 1;
    else if(nameR == "Charmander")
        j = 2;
    else if(nameR == "Squirtle")
        j = 3;
    else if(nameR == "Licktung")
        j = 4;
    else if(nameR == "Muk")
        j = 5;
    else if(nameR == "Krabby")
        j = 6;
    else if(nameR == "Shellder")
        j = 7;
    else if(nameR == "Onix")
        j = 8;
    else if(nameR == "Geodude")
        j = 9;
    else if(nameR == "Bulbasaur")
        j = 10;
    else if(nameR == "Pidgeotto")
        j = 11;
    else
        j = 12;
    leftPoke *lp = new leftPoke(i);
    rightPoke *rp = new rightPoke(j);
    scene->addItem(lp);
    scene->addItem(rp);
    ui->myHp->setMaximum(my->getFullHp());
    ui->myHp->setMinimum(0);
    ui->enmHp->setMaximum(enm->getFullHp());
    ui->enmHp->setMinimum(0);
}

void Battleground::on_battleBtn_clicked()
{
    thread->start();
    ui->battleBtn->setEnabled(0);
}

