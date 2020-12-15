/*
 *
 *登陆主界面
 *
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employees_interface.h"
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    admin = nullptr;

    /*设置样式*/
    QFile file(":./mystyle.qss");

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        //qApp 它是一个 宏定义，是一个函数的函数返回 值，返回该应用程序中，只有一个qApp对象

        //#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))
        qApp->setStyleSheet(data);
    }
    file.close();

    /*读取货物文件信息到容器*/
    QFile account_file;
    account_file.setFileName("./all_info.json");

    if(account_file.open(QIODevice::ReadOnly))
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
    else   //没有就创建
    {
        account_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("account", "root");
        object1.insert("passwd", "123123");

        QJsonArray array;

        array.insert(0, object1);

        QJsonObject object2;
        object2.insert("info", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        account_file.write(data);

    }
    account_file.close();
}
static int times = 0;
MainWindow::~MainWindow()
{
    delete ui;
}

/*管理员登录按钮*/
void MainWindow::on_management_Button_clicked()
{
    QMessageBox a;
    if(ui->account_Edit->text() == "admin" && ui->passwd_Edit->text() == "123123")
    {

        admin = new Admin(this);

        admin->show();

        this->hide();
    }
    else
    {
        a.information(nullptr, "提示", QString("管理员账号或密码错误!!!!"));
    }
}

/*员工登录按钮*/
void MainWindow::on_employees_Button_clicked()
{
    QMessageBox a;
    for (int i = 0; i < employees_list.size(); i++)
    {
        if(employees_list.at(i).value("account").toString() == ui->account_Edit->text())

        {
            if( employees_list.at(i).value("passwd").toString() == ui->passwd_Edit->text())
            {
                Employees_interface* employees = new Employees_interface;
                employees->show();
                connect(this, &MainWindow::send, employees, &Employees_interface::recv);
                emit send(ui->account_Edit->text());
                delete this;
                return;
            }
            else
            {
                a.information(nullptr, "提示", QString("您已经输错了密码%1次").arg(++times));
                /*判断输错密码次数*/
                if(times == 3)
                {
                    QMessageBox* m_box = new QMessageBox(QMessageBox::Information, QString("提示"), QString("还剩3秒退出"));
                    //三秒后退出
                    QTimer::singleShot(3000, m_box, SLOT(accept()));
                    m_box->exec();
                    times = 0;
                    this->close();
                }
                return;
            }
        }

    }
    /*遍历完没有就说明没有注册*/
    a.information(nullptr, "提示", QString("该账户未注册！！！"));
}
