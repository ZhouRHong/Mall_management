/*
 *
 *采购查询模块
 *
 */

#include "check.h"
#include "ui_check.h"
#include "goods.h"
Check::Check(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Check)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    QString label;
    label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
    ui->listWidget->addItem(label);

    /*读取文件信息到容器*/
    goods_file.setFileName("./goods.json");

    if(goods_file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  goods_file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(array);

        QJsonObject object = doc.object();

        QJsonArray jsonArray =   object.value("goods").toArray();

        for (int i = 0; i < jsonArray.size(); i++)
        {
            employees_list.append(jsonArray.at(i).toObject());
        }
    }
    else
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
            employees_list.append(array.at(i).toObject());
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

Check::~Check()
{
    delete ui;
}


/*种类查询按钮*/
void Check::on_category_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
    ui->listWidget->addItem(label);

    /*遍历容器查找总类相同的货物添加到条目*/
    for (int i = 0; i < employees_list.size(); i++)
    {
        if(employees_list.at(i).value("category").toString() == ui->category_Edit->text())
        {
            label = employees_list.at(i).value("category").toString() + "\t"
                    + employees_list.at(i).value("name").toString() + "\t"
                    + employees_list.at(i).value("in_num").toString() + "\t"
                    + employees_list.at(i).value("in_price").toString() + "\t"
                    + employees_list.at(i).value("out_price").toString();
            ui->listWidget->addItem(label);

        }
    }

}

/*商品名查询按钮*/
void Check::on_name_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
    ui->listWidget->addItem(label);

    /*遍历容器查找名字相同的货物添加到条目*/
    for (int i = 0; i < employees_list.size(); i++)
    {
        if(employees_list.at(i).value("name").toString() == ui->name_Edit->text())
        {
            label = employees_list.at(i).value("category").toString() + "\t"
                    + employees_list.at(i).value("name").toString() + "\t"
                    + employees_list.at(i).value("in_num").toString() + "\t"
                    + employees_list.at(i).value("in_price").toString() + "\t"
                    + employees_list.at(i).value("out_price").toString();
            ui->listWidget->addItem(label);

        }
    }
}

/*价格查询按钮*/
void Check::on_price_Button_clicked()
{
    QString label;
    ui->listWidget->clear();
    label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
    ui->listWidget->addItem(label);

    /*遍历容器查找出货价格小于输入价格的货物添加到条目*/
    for (int i = 0; i < employees_list.size(); i++)
    {
        qDebug() << employees_list.at(i).value("out_price").toString().toFloat();
        if(employees_list.at(i).value("out_price").toString().toFloat() <= ui->price_Edit->text().toFloat())
        {
            label = employees_list.at(i).value("category").toString() + "\t"
                    + employees_list.at(i).value("name").toString() + "\t"
                    + employees_list.at(i).value("in_num").toString() + "\t"
                    + employees_list.at(i).value("in_price").toString() + "\t"
                    + employees_list.at(i).value("out_price").toString();
            ui->listWidget->addItem(label);
        }
        else
        {
            ui->listWidget->clear();
            label = "商品种类 | 商品名称 | 商品数量 | 商品价格";
            ui->listWidget->addItem(label);
        }
    }
}

/*返回按钮*/
void Check::on_back_Button_clicked()
{
    Goods* goods = new Goods;
    goods->show();
    delete this;
}
