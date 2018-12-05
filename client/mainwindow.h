#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>
#include <QStandardItemModel>

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

private:
    Ui::MainWindow *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    bool state = 1;
};

#endif // MAINWINDOW_H
