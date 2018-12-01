#ifndef USERIN_H
#define USERIN_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtNetwork>
#include <unistd.h>

namespace Ui {
class UserIn;
}

class UserIn : public QDialog
{
    Q_OBJECT

public:
    explicit UserIn(QWidget *parent = nullptr);
    ~UserIn();

private slots:
    void on_loginBtn_clicked();

    void dealDatagram();

private:
    Ui::UserIn *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    int tOrF = 4;
};

#endif // USERIN_H
