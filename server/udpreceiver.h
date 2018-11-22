#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDebug>
#include "database.h"

namespace Ui {
class udpReceiver;
}

class udpReceiver : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpReceiver(QWidget *parent = nullptr);
    ~udpReceiver();

private slots:
    void on_sendBtn_clicked();

    void dealDatagram();

    void usrs(int inOrNew);

    int userIn(QString name,QString pwd);

    bool newUsr(QString name,QString pwd);

    void txShow();

private:
    Ui::udpReceiver *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    Log *loger;
};

#endif // UDPRECEIVER_H
