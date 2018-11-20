#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QDebug>

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
};

#endif // WELCOME_H
