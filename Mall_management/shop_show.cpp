/*
 *
 *货物采购模块
 *
 */


#include "shop_show.h"
#include "ui_shop_show.h"
#include "goods.h"
Shop_show::Shop_show(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Shop_show)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    QStringList labels;
    QString label;
    labels << "家用电器" << "日常用品" << "水果" << "五金";
    ui->listWidget->addItems(labels);

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

Shop_show::~Shop_show()
{
    delete ui;
}

/*确认按钮*/
void Shop_show::on_confirm_Button_clicked()
{
    QMessageBox a;
    QJsonObject object1;
    int num = 0;
    for (int i = 0; i < employees_list.size(); i++)
    {
        /*如果采购的货物本来就有则数量累加*/
        if(employees_list.at(i).value("name").toString() == ui->name_Edit->text())
        {
            num  = ui->goods_num_spinBox->text().toInt() + employees_list.at(i).value("in_num").toString().toInt();
            employees_list.removeAt(i);
            object1.insert("category", ui->category_Edit->text());
            object1.insert("in_num", QString::number(num));
            object1.insert("in_price", ui->in_price_SpinBox->text());
            object1.insert("out_price", ui->out_price_SpinBox_2->text());
            object1.insert("name", ui->name_Edit->text());

            employees_list.append(object1);

            QJsonArray array;

            for (int i = 0; i < employees_list.size(); i++)
            {

                QJsonObject object2;
                object2.insert("category", employees_list.at(i).value("category").toString());
                object2.insert("in_num", employees_list.at(i).value("in_num").toString());
                object2.insert("out_price", employees_list.at(i).value("out_price").toString());
                object2.insert("in_price", employees_list.at(i).value("in_price").toString());
                object2.insert("name", employees_list.at(i).value("name").toString());

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
            QApplication::setQuitOnLastWindowClosed(false);
            a.information(nullptr, "提示", QString("添加成功！！！"));

            return;
        }
    }

    /*如果货物本来没有则添加*/
    object1.insert("category", ui->category_Edit->text());
    object1.insert("in_num", ui->goods_num_spinBox->text());
    object1.insert("in_price", ui->in_price_SpinBox->text());
    object1.insert("out_price", ui->out_price_SpinBox_2->text());
    object1.insert("name", ui->name_Edit->text());

    employees_list.append(object1);
    QJsonArray array;
    for (int i = 0; i < employees_list.size(); i++)
    {
        QJsonObject object2;
        object2.insert("category", employees_list.at(i).value("category").toString());
        object2.insert("in_num", employees_list.at(i).value("in_num").toString());
        object2.insert("out_price", employees_list.at(i).value("out_price").toString());
        object2.insert("in_price", employees_list.at(i).value("in_price").toString());
        object2.insert("name", employees_list.at(i).value("name").toString());

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
    QApplication::setQuitOnLastWindowClosed(false);
    a.information(nullptr, "提示", QString("添加成功！！！"));
}

/*返回按钮*/
void Shop_show::on_back_Button_clicked()
{
    Goods* goods = new Goods;
    goods->show();
    delete this;
}


/*条目双击槽函数*/
void Shop_show::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    ui->category_Edit->setText(item->text());
}
