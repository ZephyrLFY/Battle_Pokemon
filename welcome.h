#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QDebug>
#include <QtNetwork>

namespace Ui {
class welcome;
}

class welcome : public QDialog
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();

private slots:
    void on_loginBtn_clicked();

    void on_logupBtn_clicked();

private:
    Ui::welcome *ui;
    QUdpSocket *sender;
};

#endif // WELCOME_H
