#ifndef USERIN_H
#define USERIN_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtNetwork>
#include <QList>
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
    qint32 tOrF = 4;
    quint16 rcv1Port;
    quint16 sendPort;
};

#endif // USERIN_H
