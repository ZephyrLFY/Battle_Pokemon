#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>

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
    void on_action_triggered();

    void on_logoutBtn_clicked();

    void on_testBtn_clicked();

    void processPendingDatagram();

private:
    Ui::MainWindow *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    bool state = 0;
};

#endif // MAINWINDOW_H
