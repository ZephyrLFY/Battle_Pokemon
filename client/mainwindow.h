#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QKeyEvent>

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

    void on_usrBtn_clicked();

    void processPendingDatagram();

    void updateUsr(QList<QString> &usrInfo);

    void updatePoke(QList<QString> &pokeInfo);

    void loseLink();

    void on_lvlBtn_clicked();

    void getUsrInfo(const QItemSelection&,const QItemSelection&);

    void getPokeInfo(const QItemSelection&,const QItemSelection&);

    void on_pokeBtn_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void initMap();

private:
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
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
