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

    void on_testBtn_clicked();

    void processPendingDatagram();

    void updateUsr(QList<QString> &usrInfo);

    void loseLink();

private:
    Ui::MainWindow *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    bool state = 1;
    //QStandardItemModel *usrModel;
    //QStandardItemModel *pokeModel;
};

#endif // MAINWINDOW_H
