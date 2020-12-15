/*
 *
 *管理员界面
 *
 */


#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "staff.h"
#include "goods.h"
Admin::Admin(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
}

Admin::~Admin()
{
    delete ui;
}

/*员工管理按钮*/
void Admin::on_employees_Button_clicked()
{

    Staff* staff = new Staff();

    staff->show();

    delete this;
}

/*货物管理按钮*/
void Admin::on_goods_Button_clicked()
{
    Goods* goods = new Goods;
    goods->show();
    delete this;
}

/*返回按钮*/
void Admin::on_pushButton_2_clicked()
{
    MainWindow* w = new MainWindow;
    w->show();
    delete this;
}
