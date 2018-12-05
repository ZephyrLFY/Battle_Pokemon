#ifndef BATTLE_H
#define BATTLE_H

#include <QWidget>

namespace Ui {
class battle;
}

class battle : public QWidget
{
    Q_OBJECT

public:
    explicit battle(QWidget *parent = nullptr);
    ~battle();

private:
    Ui::battle *ui;
};

#endif // BATTLE_H
