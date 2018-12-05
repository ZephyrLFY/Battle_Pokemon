#include "battle.h"
#include "ui_battle.h"

battle::battle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battle)
{
    ui->setupUi(this);
}

battle::~battle()
{
    delete ui;
}
