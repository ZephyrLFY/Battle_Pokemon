#ifndef POKEVIEW_H
#define POKEVIEW_H

#include <QDialog>
#include <QtNetwork>
#include <QStandardItemModel>

namespace Ui {
class pokeView;
}

class pokeView : public QDialog
{
    Q_OBJECT

public:
    explicit pokeView(QWidget *parent = nullptr);
    ~pokeView();

    void getPoke();

    void updateTable(QList<QString> &pokeInfo);

public slots:

    void processPendingDatagram();

private:
    Ui::pokeView *ui;
    QUdpSocket *sender;
    QUdpSocket *receiver;
    quint16 rcv1Port;
    quint16 sendPort;
};

#endif // POKEVIEW_H
