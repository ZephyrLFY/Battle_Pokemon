#include "userview.h"
#include "ui_userview.h"
#include "connection.h"

Userview::Userview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Userview)
{
    ui->setupUi(this);
    //Log loger;
    model = new QSqlTableModel(this);
    model->setTable("player");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setFilter("alive = '1'");
    model->select(); //选取整个表的所有行

    //不显示password属性列,如果这时添加记录，则该属性的值添加不上
    model->removeColumns(1,2);

    ui->tableView->setModel(model);

    //使其不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Userview::~Userview()
{
    delete ui;
}
