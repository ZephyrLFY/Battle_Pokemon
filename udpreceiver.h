#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class udpReceiver;
}

class udpReceiver : public QWidget
{
    Q_OBJECT

public:
    explicit udpReceiver(QWidget *parent = nullptr);
    ~udpReceiver();
    int updating();
    void whatToDo(int flag);
    void sendMsg(QString msg);

private slots:
    void processPendingDatagram();

    void on_sendBtn_clicked();

private:
    Ui::udpReceiver *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    bool tOrF;
};

#endif // UDPRECEIVER_H
