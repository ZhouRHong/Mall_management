#include "add_cashier.h"
#include "ui_add_cashier.h"
#include "staff_management.h"
Add_cashier::Add_cashier(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Add_cashier)
{
    ui->setupUi(this);

    account_file.setFileName("./all_info.json");
    if(account_file.open(QIODevice::ReadWrite ))//| QIODevice::Truncate
    {
        QByteArray array =  account_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray =   object.value("info").toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            employees_list.append(jsonArray.at(i).toObject());
        }
    }
}

Add_cashier::~Add_cashier()
{
    delete ui;
}

void Add_cashier::on_back_Button_clicked()
{
    Staff_management* management = new Staff_management;
    management->show();
    this->close();
}

void Add_cashier::on_ok_Button_clicked()
{
    QMessageBox a;
    for (int i = 0; i < employees_list.size(); i++)
    {
        if(employees_list.at(i).value("account").toString() == ui->account_Edit->text())

        {
            a.information(nullptr, "提示", QString("该账户名已经被注册！！！"));
            qDebug() << "该账户名已经被注册！！！";
        }
        else if(ui->account_Edit->text() == "admin")
        {
            a.information(nullptr, "提示", QString("您不能使用管理员账户名注册！！！"));
            qDebug() << "您不能使用管理员账户名注册！！！";
        }
        else
        {
            if(ui->pass2_Edit->text() == ui->passwd_Edit->text())
            {
                QJsonObject object1;

                object1.insert("account", ui->account_Edit->text());
                object1.insert("passwd", ui->passwd_Edit->text());
                employees_list.append(object1);
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
                a.information(nullptr, "提示", QString("添加成功！！！"));
            }
            else
            {
                a.information(nullptr, "提示", QString("两次输入密码不一致！！！"));
            }

        }
    }
}
