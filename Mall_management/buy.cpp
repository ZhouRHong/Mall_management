/*
 *
 *客户结算模块
 *
 */


#include "buy.h"
#include "ui_buy.h"
#include "employees_interface.h"
Buy::Buy(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Buy)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
    QString label;


    /*添加条目*/
    label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
    ui->listWidget->addItem(label);
    goods_file.setFileName("./goods.json");


    /*读取货物json文件到货物容器*/
    if(goods_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray =   object.value("goods").toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            list.append(jsonArray.at(i).toObject());
            label = list.at(i).value("category").toString() + "\t"
                    + list.at(i).value("name").toString() + "\t"
                    + list.at(i).value("in_num").toString() + "\t"
                    + list.at(i).value("out_price").toString();
            ui->listWidget->addItem(label);
        }
    }
    else //没有则创建
    {
        goods_file.open(QIODevice::ReadWrite | QIODevice::Append);

        QJsonObject object1;

        object1.insert("category", "水果");
        object1.insert("name", "苹果");
        object1.insert("in_num", "1");
        object1.insert("in_price", "1.00");
        object1.insert("out_price", "1.00");

        QJsonArray array;

        array.insert(0, object1);
        for (int i = 0; i < array.size(); i++)
        {
            list.append(array.at(i).toObject());
            label = list.at(i).value("category").toString() + "\t"
                    + list.at(i).value("name").toString() + "\t"
                    + list.at(i).value("in_num").toString() + "\t"
                    + list.at(i).value("out_price").toString();
            ui->listWidget->addItem(label);
        }
        QJsonObject object2;
        object2.insert("goods", array);

        QJsonDocument doc;
        doc.setObject(object2);

        QByteArray data = doc.toJson();

        goods_file.write(data);

    }
    goods_file.close();


}

Buy::~Buy()
{
    delete ui;
}

/*返回按钮*/
void Buy::on_back_Button_clicked()
{
    Employees_interface* employees = new Employees_interface;
    employees->show();
    connect(this, &Buy::back_account, employees, &Employees_interface::recv_back_account);
    emit back_account(ui->account_label->text());
    delete this;
}


/*确认购买按钮*/
void Buy::on_buy_Button_clicked()
{
    QMessageBox a;
    QJsonObject object1;
    int num = 0;
    QString label;

    /*拼接购物清单文件名*/
    QString path = "./" + this->account + ".json";
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
            shop_list.append(jsonArray.at(i).toObject());
        }
    }
    else   //没有则创建
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


    /*购买前先遍历*/
    for (int i = 0; i < list.size(); i++)
    {
        /*先找到要购买的货物名*/
        if(list.at(i).value("name").toString() == ui->name_Edit->text())
        {
            /*计算购买后的数量用作判断*/
            num  = list.at(i).value("in_num").toString().toInt() - ui->num_Edit->text().toInt();
            if(num < 0)
            {
                a.information(nullptr, "提示", QString("存货不足！！！"));
                return;
            }
            //货物数量为0后
            else if (num == 0)
            {
                /*先将购买到的商品放到容器，然后将容器全部的数据以只写并且清空的方式写入文件*/
                goods_list_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                QJsonObject sobject1;
                float total_price;
                total_price = ui->num_Edit->text().toFloat() * list.at(i).value("out_price").toString().toFloat();
                sobject1.insert("category", list.at(i).value("category").toString());
                sobject1.insert("name", list.at(i).value("name").toString());
                sobject1.insert("num", ui->num_Edit->text());
                sobject1.insert("total_price", QString::number(total_price));

                shop_list.append(sobject1);
                QJsonArray sarray;
                for (int i = 0; i < shop_list.size(); i++)
                {
                    QJsonObject sobject2;
                    sobject2.insert("category", shop_list.at(i).value("category").toString());
                    sobject2.insert("name", shop_list.at(i).value("name").toString());
                    sobject2.insert("num", shop_list.at(i).value("num").toString());
                    sobject2.insert("total_price", shop_list.at(i).value("total_price").toString());

                    sarray.insert(i, sobject2);
                }
                QJsonObject sobject3;
                sobject3.insert(ui->account_label->text(), sarray);
                QJsonDocument sdoc;
                sdoc.setObject(sobject3);

                QByteArray sdata = sdoc.toJson();

                goods_list_file.write(sdata);
                goods_list_file.close();
                shop_list.clear();


                //========================================================================

                /*在货物容器先删除余货为0的货物对象*/
                list.removeAt(i);

                QJsonArray array;

                for (int i = 0; i < list.size(); i++)
                {

                    QJsonObject object2;
                    object2.insert("category", list.at(i).value("category").toString());
                    object2.insert("in_num", list.at(i).value("in_num").toString());
                    object2.insert("out_price", list.at(i).value("out_price").toString());
                    object2.insert("in_price", list.at(i).value("in_price").toString());
                    object2.insert("name", list.at(i).value("name").toString());

                    array.insert(i, object2);
                }
                QJsonObject object3;
                object3.insert("goods", array);
                QJsonDocument doc;
                doc.setObject(object3);

                QByteArray data = doc.toJson();

                /*将操作完的容器数据以只写并且清空的方式写入文件*/
                goods_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                goods_file.write(data);
                goods_file.close();
                QApplication::setQuitOnLastWindowClosed(false);
                a.information(nullptr, "提示", QString("购买成功！！！"));

                ui->listWidget->clear();
                label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
                ui->listWidget->addItem(label);

                /*将货物容器里的货物信息添加到条目上*/
                for (int i = 0; i < list.size(); i++)
                {
                    label = list.at(i).value("category").toString() + "\t"
                            + list.at(i).value("name").toString() + "\t"
                            + list.at(i).value("in_num").toString() + "\t"
                            + list.at(i).value("out_price").toString();
                    ui->listWidget->addItem(label);
                }
                return;
            }
            else
            {
                /*先将购买到的商品放到容器，然后将容器全部的数据以只写并且清空的方式写入文件*/
                goods_list_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                QJsonObject sobject1;
                float total_price;
                total_price = ui->num_Edit->text().toFloat() * list.at(i).value("out_price").toString().toFloat();
                sobject1.insert("category", list.at(i).value("category").toString());
                sobject1.insert("name", list.at(i).value("name").toString());

                /*把购买数量取下*/
                sobject1.insert("num", ui->num_Edit->text());
                sobject1.insert("total_price", QString::number(total_price));

                shop_list.append(sobject1);
                QJsonArray sarray;
                for (int i = 0; i < shop_list.size(); i++)
                {
                    QJsonObject sobject2;
                    sobject2.insert("category", shop_list.at(i).value("category").toString());
                    sobject2.insert("name", shop_list.at(i).value("name").toString());
                    sobject2.insert("num", shop_list.at(i).value("num").toString());
                    sobject2.insert("total_price", shop_list.at(i).value("total_price").toString());

                    sarray.insert(i, sobject2);
                }
                QJsonObject sobject3;
                sobject3.insert(ui->account_label->text(), sarray);
                QJsonDocument sdoc;
                sdoc.setObject(sobject3);

                QByteArray sdata = sdoc.toJson();


                /*写入文件*/
                goods_list_file.write(sdata);
                goods_list_file.close();
                shop_list.clear();
                //================================================================

                /*将货物的数量重新计算后写入文件*/
                QJsonObject object1;
                object1.insert("category", list.at(i).value("category").toString());
                object1.insert("in_num", QString::number(num));
                object1.insert("out_price", list.at(i).value("out_price").toString());
                object1.insert("in_price", list.at(i).value("in_price").toString());
                object1.insert("name", list.at(i).value("name").toString());
                list.removeAt(i);
                list.append(object1);

                QJsonArray array;

                for (int i = 0; i < list.size(); i++)
                {
                    QJsonObject object2;
                    object2.insert("category", list.at(i).value("category").toString());
                    object2.insert("in_num", list.at(i).value("in_num").toString());
                    object2.insert("out_price", list.at(i).value("out_price").toString());
                    object2.insert("in_price", list.at(i).value("in_price").toString());
                    object2.insert("name", list.at(i).value("name").toString());

                    array.insert(i, object2);
                }
                QJsonObject object3;
                object3.insert("goods", array);
                QJsonDocument doc;
                doc.setObject(object3);

                QByteArray data = doc.toJson();
                goods_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                goods_file.write(data);
                goods_file.close();

                // QApplication::setQuitOnLastWindowClosed(false);
                a.information(nullptr, "提示", QString("购买成功！！！"));


                ui->listWidget->clear();

                label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
                ui->listWidget->addItem(label);

                /*将货物容器里的货物信息添加到条目*/
                for (int i = 0; i < list.size(); i++)
                {
                    label = list.at(i).value("category").toString() + "\t"
                            + list.at(i).value("name").toString() + "\t"
                            + list.at(i).value("in_num").toString() + "\t"
                            + list.at(i).value("out_price").toString();
                    ui->listWidget->addItem(label);
                }
                return;
            }
        }
    }
    a.information(nullptr, "提示", QString("没有此商品！！！"));
}


/*接收信号（账号）槽函数*/
void Buy::recv_account(QString account)
{
    this->account = account;
    ui->account_label->setText(account);
}
