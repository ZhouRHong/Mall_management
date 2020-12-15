/*
 *
 *员工主界面
 *
 */


#include "employees_interface.h"
#include "ui_employees_interface.h"
#include "mainwindow.h"
#include "buy.h"
#include "order.h"
Employees_interface::Employees_interface(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Employees_interface)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

Employees_interface::~Employees_interface()
{
    delete ui;
}

/*返回按钮*/
void Employees_interface::on_pushButton_2_clicked()
{
    MainWindow* w = new MainWindow;
    w->show();
    delete this;
}

/*客户结算按钮*/
void Employees_interface::on_customer_Button_clicked()
{
    Buy* buy = new Buy;
    buy->show();
    connect(this, &Employees_interface::send_account, buy, &Buy::recv_account);

    /*将账号信息发送到buy界面*/
    emit send_account(ui->label->text());
    delete this;
}

/*订单查询按钮*/
void Employees_interface::on_goods_Button_clicked()
{
    Order* order = new Order;
    order->show();
    connect(this, &Employees_interface::send_account, order, &Order::recv);

    /*将账号信息发送到order界面*/
    emit send_account(ui->label->text());
    delete this;
}

/*信号（账号）接收槽函数*/
void Employees_interface::recv(QString account)
{
    ui->label->setText(account);
}

/*信号（账号）接收槽函数*/
void Employees_interface::recv_back_account(QString account)
{
    ui->label->setText(account);
}
