#include "admin_show.h"
#include "ui_admin_show.h"
#include "mainwindow.h"
#include "staff_management.h"
Admin_show::Admin_show(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Admin_show)
{
    ui->setupUi(this);
}

Admin_show::~Admin_show()
{
    delete ui;
}

void Admin_show::on_employees_Button_clicked()
{
    Staff_management* management = new Staff_management;
    management->show();
    this->close();
}

void Admin_show::on_goods_Button_clicked()
{

}

void Admin_show::on_pushButton_clicked()
{
    // this->parentWidget()->show();
    MainWindow* w = new MainWindow;
    w->show();
    this->close();
}
