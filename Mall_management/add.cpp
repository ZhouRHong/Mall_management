/*
 *
 *添加员工模块
 *
 */

#include "add.h"
#include "ui_add.h"
#include "staff.h"
Add::Add(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    /*读取文件到容器*/
    account_file.setFileName("./all_info.json");
    if(account_file.open(QIODevice::ReadOnly))//
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
    account_file.close();
}

Add::~Add()
{
    delete ui;
}

/*确认按钮*/
void Add::on_ok_Button_clicked()
{
    QMessageBox a;
    /*判断账户是否重复或者为管理账户*/
    for (int i = 0; i < employees_list.size(); i++)
    {
        if(employees_list.at(i).value("account").toString() == ui->account_Edit->text())
        {
            QApplication::setQuitOnLastWindowClosed(false);
            a.information(nullptr, "提示", QString("该账户名已经被注册！！！"));
            return;
        }
        else if(ui->account_Edit->text() == "admin")
        {
            QApplication::setQuitOnLastWindowClosed(false);
            a.information(nullptr, "提示", QString("您不能使用管理员账户名注册！！！"));
            qDebug() << "您不能使用管理员账户名注册！！！";
            return;
        }

    }

    if(ui->pass2_Edit->text() == ui->passwd_Edit->text())
    {
        account_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
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
        QApplication::setQuitOnLastWindowClosed(false);
        a.information(nullptr, "提示", QString("添加成功！！！"));
        account_file.close();
        return;
    }
    else
    {
        QApplication::setQuitOnLastWindowClosed(false);
        a.information(nullptr, "提示", QString("两次输入密码不一致！！！"));
        return;
    }

}

/*返回按钮*/
void Add::on_back_Button_clicked()
{
    Staff* staff = new Staff;
    staff->show();
    delete this;
}
