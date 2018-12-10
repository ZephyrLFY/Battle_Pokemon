#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wideuse.h"
#include "logout.h"
#include "userview.h"
#include "pokeview.h"
#include "mymap.h"
#include "prebtl.h"
#include "battleground.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bindPort();
    initLocalUser();
    initMap();
}

MainWindow::~MainWindow()
{
    if(state)
        loseLink();
    delete sender;
    delete receiver;
    delete zhi;
    scene->clear();
    delete scene;
    delete ui;
}

void MainWindow::bindPort()
{
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    rcv1Port = rcvPort;
    while(!receiver->bind(rcv1Port,QUdpSocket::DontShareAddress))
        rcv1Port = rcv1Port + 2;
    sendPort = rcv1Port + 1;
    sender->bind(sendPort,QUdpSocket::DontShareAddress);
    connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
}

void MainWindow::initLocalUser()
{
    QList<QString> text;
    text << "7" << localUser->getName();
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
    receiver->waitForReadyRead();
    processPendingDatagram();
}

void MainWindow::initScene()
{
    scene->setSceneRect(100 , 20 , 400, 250);
}

void MainWindow::initMap()
{
    scene = new QGraphicsScene(this);
    initScene();
    ui->wow->setScene(scene);
    zhi = new Man;
    Arena *arena = new Arena(290,40);
    Gym *gym = new Gym(470,120);
    Music *music = new Music(360,240);
    Exit *exit = new Exit(130,230);
    scene->addItem(zhi);
    scene->addItem(arena);
    scene->addItem(gym);
    scene->addItem(music);
    scene->addItem(exit);
    scene->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_W:keyUp();break;
    case Qt::Key_A:keyLeft();break;
    case Qt::Key_D:keyRight();break;
    case Qt::Key_S:keyDown();break;
    default:break;
    }
    //qDebug() << zhi->pos() << endl;
}

void MainWindow::keyUp()
{
    zhi->moveBy(0,-10);
    if(zhi->pos().ry() < 250 &&zhi->pos().ry() > 190 && zhi->pos().rx() <= 150 && zhi->pos().rx() >= 90)
    {
        on_logoutBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 60 &&zhi->pos().ry() > 0 && zhi->pos().rx() <= 310 && zhi->pos().rx() >= 250)
    {
        on_btlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 140 &&zhi->pos().ry() > 80 && zhi->pos().rx() <= 490 && zhi->pos().rx() >= 430)
    {
        on_lvlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 260 &&zhi->pos().ry() > 200 && zhi->pos().rx() <= 380 && zhi->pos().rx() >= 320)
    {
        on_musicBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < -10)
        zhi->setY(270);
}

void MainWindow::keyDown()
{
    zhi->moveBy(0,10);
    if(zhi->pos().ry() < 250 && zhi->pos().ry() > 190 && zhi->pos().rx() <= 150 && zhi->pos().rx() >= 90)
    {
        on_logoutBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 60 &&zhi->pos().ry() > 0 && zhi->pos().rx() <= 310 && zhi->pos().rx() >= 250)
    {
        on_btlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 140 &&zhi->pos().ry() > 80 && zhi->pos().rx() <= 490 && zhi->pos().rx() >= 430)
    {
        on_lvlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 260 &&zhi->pos().ry() > 200 && zhi->pos().rx() <= 380 && zhi->pos().rx() >= 320)
    {
        on_musicBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() > 270)
        zhi->setY(-10);
}

void MainWindow::keyRight()
{
    zhi->moveBy(10,0);
    if(zhi->pos().rx() > 90 && zhi->pos().rx() < 150 && zhi->pos().ry() >= 190 && zhi->pos().ry() <= 250)
    {
        on_logoutBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 60 &&zhi->pos().ry() > 0 && zhi->pos().rx() <= 310 && zhi->pos().rx() >= 250)
    {
        on_btlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 140 &&zhi->pos().ry() > 80 && zhi->pos().rx() <= 490 && zhi->pos().rx() >= 430)
    {
        on_lvlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 260 &&zhi->pos().ry() > 200 && zhi->pos().rx() <= 380 && zhi->pos().rx() >= 320)
    {
        on_musicBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().rx() > 490)
        zhi->setX(80);
}

void MainWindow::keyLeft()
{
    zhi->moveBy(-10,0);
    if(zhi->pos().rx() > 90 && zhi->pos().rx() < 150 && zhi->pos().ry() >= 190 && zhi->pos().ry() <= 250)
    {
        on_logoutBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 60 &&zhi->pos().ry() > 10 && zhi->pos().rx() <= 310 && zhi->pos().rx() >= 250)
    {
        on_btlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 140 &&zhi->pos().ry() > 80 && zhi->pos().rx() <= 490 && zhi->pos().rx() >= 430)
    {
        on_lvlBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().ry() < 260 &&zhi->pos().ry() > 200 && zhi->pos().rx() <= 380 && zhi->pos().rx() >= 320)
    {
        on_musicBtn_clicked();
        zhi->setPos(290,120);
    }
    if(zhi->pos().rx() < 80)
        zhi->setX(490);
}

void MainWindow::on_lvlBtn_clicked()
{
    localUser->whichBattle(1);
    if(isMusic)
        player->pause();
    preBtl lvlup;
    if(lvlup.exec() == QDialog::Accepted)
    {
        Battleground *btl = new Battleground;
        btl->exec();
    }
    else
    {
        if(isMusic)
            player->play();
    }
}

void MainWindow::on_action_triggered()
{
    userView viewer;
    viewer.exec();
}

void MainWindow::on_action_2_triggered()
{
    pokeView viewer;
    viewer.exec();
}

void MainWindow::on_musicBtn_clicked()
{
    if(!isMusic)
    {
        player = new QMediaPlayer(this);
        playlist = new QMediaPlaylist(this);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playlist->addMedia(QUrl::fromLocalFile("/Users/zephyr/Desktop/TOEFL/bgm1.mp3"));
        playlist->addMedia(QUrl::fromLocalFile("/Users/zephyr/Desktop/TOEFL/bgm2.mp3"));
        player->setPlaylist(playlist);
        player->play();
        isMusic = 1;
        isPlaying = 1;
    }
    else
    {
        if(isPlaying)
        {
            player->pause();
            isPlaying = 0;
        }
        else
        {
            player->play();
            isPlaying = 1;
        }
    }
}

void MainWindow::loseLink()
{
    QList<QString> text;
    text << "4" << localUser->getName();
    QByteArray temp;
    QDataStream stream(&temp, QIODevice::WriteOnly);
    stream << text;
    sender->writeDatagram(temp,QHostAddress::Broadcast,45454);
}

void MainWindow::on_logoutBtn_clicked()
{
    logout sure;
    if(sure.exec() == QDialog::Accepted)
    {
        loseLink();
        receiver->waitForReadyRead();
        processPendingDatagram();
        if(state == 0)
            QMessageBox::warning(this,"注销失败","请重试。",QMessageBox::Yes);
        else
            this->close();
    }
}

void MainWindow::processPendingDatagram()
{
    while(receiver->hasPendingDatagrams())
    {
       QByteArray datagram;
       datagram.resize(receiver->pendingDatagramSize());
       receiver->readDatagram(datagram.data(),datagram.size());
       if(datagram.size() == 1)
           if(QString::fromUtf8(datagram) == "0")
               state = 0;
           else;
       else
       {
           QList<QString> infoM;
           QDataStream stream(&datagram, QIODevice::ReadOnly);
           stream >> infoM;
           infoM.removeFirst();
           localUser->initUsr(infoM);
       }
    }
}


void MainWindow::on_btlBtn_clicked()
{
    if(!isMusic)
        return;
    else
    {
        int currentIndex = playlist->currentIndex();
        if(++currentIndex==playlist->mediaCount())
            currentIndex=0;
        playlist->setCurrentIndex(currentIndex);
        player->play();
    }
}
