#include "staff_management.h"
#include "ui_staff_management.h"
#include "admin_show.h"
#include "add_cashier.h"
Staff_management::Staff_management(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Staff_management)
{
    ui->setupUi(this);
}

Staff_management::~Staff_management()
{
    delete ui;
}

void Staff_management::on_add_Button_clicked()
{
    Add_cashier* add_cashier = new Add_cashier;
    add_cashier->show();
    this->close();
}

void Staff_management::on_backe_Button_clicked()
{
    Admin_show* admin_show = new Admin_show;
    admin_show->show();
    this->close();
}
