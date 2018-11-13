#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Newuser;
}

class Newuser : public QDialog
{
    Q_OBJECT

public:
    explicit Newuser(QWidget *parent = nullptr);
    ~Newuser();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::Newuser *ui;
};

#endif // NEWUSER_H
