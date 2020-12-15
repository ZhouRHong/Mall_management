/*
 *
 *员工管理主界面
 *
 */


#include "staff.h"
#include "ui_staff.h"
#include "admin.h"
#include <delete.h>
Staff::Staff(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

}

Staff::~Staff()
{
    delete ui;
}


/*添加员工按钮*/
void Staff::on_add_Button_clicked()
{

    Add* add = new Add();

    add->show();

    delete this;
}


/*删除按钮*/
void Staff::on_delet_Button_clicked()
{
    Delete* delete1 = new Delete;
    delete1->show();
    delete this;
}


/*返回按钮*/
void Staff::on_backe_Button_clicked()
{
    Admin* admin = new Admin;
    admin->show();
    delete this;

}
