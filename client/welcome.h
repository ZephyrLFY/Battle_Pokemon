#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>

namespace Ui {
class welcome;
}

class welcome : public QDialog
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();

    void initScene();

private slots:
    void on_loginBtn_clicked();

    void on_logupBtn_clicked();

private:
    Ui::welcome *ui;
    QGraphicsScene *scene;
    QPixmap *pix;
};

#endif // WELCOME_H
