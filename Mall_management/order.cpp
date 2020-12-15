/*
 *
 *订单查询模块
 *
 */



#include "order.h"
#include "ui_order.h"
#include "employees_interface.h"
Order::Order(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 购买数量 | 总价格";
    ui->listWidget->addItem(label);
}

Order::~Order()
{
    delete ui;
}

/*返回按钮*/
void Order::on_back_Button_clicked()
{
    Employees_interface* employees = new Employees_interface;
    employees->show();

    /*返回的时候把，账号也用信号发回去*/
    connect(this, &Order::back_account, employees, &Employees_interface::recv_back_account);
    emit back_account(ui->account_label->text());
    delete this;
}


/*一键查询按钮*/
void Order::on_fast_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 购买数量 | 总价格";
    ui->listWidget->addItem(label);

    /*拼接文件路径*/
    QString path = "./" + ui->account_label->text() + ".json";
    goods_list_file.setFileName(path);

    /*读取购买清单*/
    if(goods_list_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_list_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray = object.value(ui->account_label->text()).toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            label = jsonArray.at(i).toObject().value("category").toString() + "\t"
                    + jsonArray.at(i).toObject().value("name").toString() + "\t"
                    + jsonArray.at(i).toObject().value("num").toString() + "\t"
                    + jsonArray.at(i).toObject().value("total_price").toString();
            ui->listWidget->addItem(label);
        }
    }
    else
    {
        goods_list_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("category", "水果");
        object1.insert("name", "苹果");
        object1.insert("num", "1");
        object1.insert("total_price", "1.00");

        QJsonArray array;

        array.insert(0, object1);
        for (int i = 0; i < array.size(); i++)
        {
            shop_list.append(array.at(i).toObject());
        }
        QJsonObject object2;
        object2.insert("goods_list", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        goods_list_file.write(data);

    }
    goods_list_file.close();
}

/*种类查询按钮*/
void Order::on_category_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 购买数量 | 总价格";
    ui->listWidget->addItem(label);

    QString path = "./" + ui->account_label->text() + ".json";
    goods_list_file.setFileName(path);

    /*读取购买清单*/
    if(goods_list_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_list_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray = object.value(ui->account_label->text()).toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {

            if(jsonArray.at(i).toObject().value("category").toString() == ui->category_Edit->text())
            {
                qDebug() << jsonArray.at(i).toObject().value("name").toString();
                qDebug() << ui->category_Edit->text();
                label = jsonArray.at(i).toObject().value("category").toString() + "\t"
                        + jsonArray.at(i).toObject().value("name").toString() + "\t"
                        + jsonArray.at(i).toObject().value("num").toString() + "\t"
                        + jsonArray.at(i).toObject().value("total_price").toString();
                ui->listWidget->addItem(label);
            }
        }
    }
    else
    {
        goods_list_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("category", "水果");
        object1.insert("name", "苹果");
        object1.insert("num", "1");
        object1.insert("total_price", "1.00");

        QJsonArray array;

        array.insert(0, object1);
        for (int i = 0; i < array.size(); i++)
        {
            shop_list.append(array.at(i).toObject());
        }
        QJsonObject object2;
        object2.insert("goods_list", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        goods_list_file.write(data);

    }
    goods_list_file.close();
}

/*商品名查询按钮*/
void Order::on_name_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 购买数量 | 总价格";
    ui->listWidget->addItem(label);

    QString path = "./" + ui->account_label->text() + ".json";
    goods_list_file.setFileName(path);

    /*读取购买清单*/
    if(goods_list_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_list_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray = object.value(ui->account_label->text()).toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            if(jsonArray.at(i).toObject().value("name").toString() == ui->name_Edit->text())
            {
                label = jsonArray.at(i).toObject().value("category").toString() + "\t"
                        + jsonArray.at(i).toObject().value("name").toString() + "\t"
                        + jsonArray.at(i).toObject().value("num").toString() + "\t"
                        + jsonArray.at(i).toObject().value("total_price").toString();
                ui->listWidget->addItem(label);
            }

        }
    }
    else
    {
        goods_list_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("category", "水果");
        object1.insert("name", "苹果");
        object1.insert("num", "1");
        object1.insert("total_price", "1.00");

        QJsonArray array;

        array.insert(0, object1);
        for (int i = 0; i < array.size(); i++)
        {
            shop_list.append(array.at(i).toObject());
        }
        QJsonObject object2;
        object2.insert("goods_list", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        goods_list_file.write(data);

    }
    goods_list_file.close();
}

/*价格查询按钮*/
void Order::on_price_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 购买数量 | 总价格";
    ui->listWidget->addItem(label);

    QString path = "./" + ui->account_label->text() + ".json";
    goods_list_file.setFileName(path);

    /*读取购买清单*/
    if(goods_list_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_list_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray = object.value(ui->account_label->text()).toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            if(jsonArray.at(i).toObject().value("total_price").toString().toFloat() <= ui->price_Edit->text().toFloat())
            {
                label = jsonArray.at(i).toObject().value("category").toString() + "\t"
                        + jsonArray.at(i).toObject().value("name").toString() + "\t"
                        + jsonArray.at(i).toObject().value("num").toString() + "\t"
                        + jsonArray.at(i).toObject().value("total_price").toString();
                ui->listWidget->addItem(label);
            }

        }
    }
    else
    {
        goods_list_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("category", "水果");
        object1.insert("name", "苹果");
        object1.insert("num", "1");
        object1.insert("total_price", "1.00");

        QJsonArray array;

        array.insert(0, object1);
        for (int i = 0; i < array.size(); i++)
        {
            shop_list.append(array.at(i).toObject());
        }
        QJsonObject object2;
        object2.insert("goods_list", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        goods_list_file.write(data);

    }
    goods_list_file.close();
}

/*信号（账号）接收槽函数*/
void Order::recv(QString account)
{
    ui->account_label->setText(account);
}
