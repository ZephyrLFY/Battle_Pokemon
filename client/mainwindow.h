#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_logoutBtn_clicked();

    void processPendingDatagram();

    void loseLink();

    void on_lvlBtn_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void initMap();

    void on_musicBtn_clicked();

    void initLocalUser();

    void on_btlBtn_clicked();

private:
    void bindPort();

    void initScene();

    void initSceneBackground();

    void keyPressEvent(QKeyEvent *e);

    void keyUp();

    void keyLeft();

    void keyRight();

    void keyDown();

    Ui::MainWindow *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    quint16 rcv1Port;
    quint16 sendPort;
    bool state = 1;
    bool isMusic = 0;
    bool isPlaying = 0;
    QGraphicsScene *scene;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QGraphicsItem *zhi;
};

#endif // MAINWINDOW_H
