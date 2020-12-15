/*
 *
 *删除员工模块
 *
 */

#include "delete.h"
#include "ui_delete.h"
#include <staff.h>
Delete::Delete(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Delete)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    account_file.setFileName("./all_info.json");

    QString label;

    /*先将员工信息存到容器里并且添加到条目*/
    if(account_file.open(QIODevice::ReadOnly))//
    {
        QByteArray array =  account_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray =   object.value("info").toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            employees_list.append(jsonArray.at(i).toObject());
            label = QString::number(i) +
                    "    " + jsonArray.at(i).toObject().value("account").toString() +
                    "   " + jsonArray.at(i).toObject().value("passwd").toString();
            ui->info_Widget->addItem(label);
        }
    }
    account_file.close();
}

Delete::~Delete()
{
    delete ui;
}


/*删除按钮*/
void Delete::on_delete_Button_clicked()
{
    QMessageBox a;
    account_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    employees_list.removeAt(ui->num_Edit->text().toInt());


    QMessageBox* Msgbox = new QMessageBox;
    Msgbox->setWindowTitle("确认提示框");
    Msgbox->setText("请问是否要删除员工");
    QPushButton* btn1 = Msgbox->addButton("确认", QMessageBox::YesRole);
    QPushButton* btn2 = Msgbox->addButton("取消", QMessageBox::NoRole);
    QString label;
    switch (Msgbox->exec())
    {
        case 0:
            delete_info();
            QApplication::setQuitOnLastWindowClosed(false);
            a.information(nullptr, "提示", QString("删除成功！！！"));
            ui->info_Widget->clear();
            for (int i = 0; i < employees_list.size(); i++)
            {
                label = QString::number(i) + "    " + employees_list.at(i).value("account").toString() +
                        "   " + employees_list.at(i).value("passwd").toString();
                ui->info_Widget->addItem(label);
            }

            break;
        case 1:
            break;
    }
}

/*删除函数*/
void Delete::delete_info()
{
    /*将文件以只写并清空的方式打开*/
    account_file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    /*将对应序号的员工删除*/
    employees_list.removeAt(ui->num_Edit->text().toInt());

    /*重新写入*/
    QJsonArray array;
    for (int i = 0; i < employees_list.size(); i++)
    {
        QJsonObject object2;
        object2.insert("account", employees_list.at(i).value("account").toString());
        object2.insert("passwd", employees_list.at(i).value("passwd").toString());

        array.insert(i, object2);
    }
    QJsonObject object3;
    object3.insert("info", array);
    QJsonDocument doc;
    doc.setObject(object3);

    QByteArray data = doc.toJson();

    account_file.write(data);
    account_file.close();
}

/*返回按钮*/
void Delete::on_back_Button_clicked()
{
    Staff* staff = new Staff;
    staff->show();
    delete this;
}

/*条目槽函数*/
void Delete::on_info_Widget_itemDoubleClicked(QListWidgetItem* item)
{
    int row = ui->info_Widget->currentRow();
    ui->num_Edit->setText(QString::number(row));
}
