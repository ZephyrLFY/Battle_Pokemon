#ifndef USERVIEW_H
#define USERVIEW_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Userview;
}

class Userview : public QDialog
{
    Q_OBJECT

public:
    explicit Userview(QWidget *parent = nullptr);
    ~Userview();

private:
    Ui::Userview *ui;
    QSqlTableModel *model;
};

#endif // USERVIEW_H
