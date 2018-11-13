#ifndef USERIN_H
#define USERIN_H

#include <QDialog>
#include <QMessageBox>

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

private:
    Ui::UserIn *ui;
};

#endif // USERIN_H
