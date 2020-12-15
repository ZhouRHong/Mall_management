#ifndef SHOP_SHOW_H
#define SHOP_SHOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtDebug>
#include <QMessageBox>
#include <synchapi.h>
#include <QTimer>
#include <QListWidget>
namespace Ui
{
    class Shop_show;
}

class Shop_show : public QMainWindow
{
    Q_OBJECT

public:
    explicit Shop_show(QWidget* parent = nullptr);
    ~Shop_show();

private slots:
    void on_confirm_Button_clicked();

    void on_back_Button_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);

private:
    Ui::Shop_show* ui;
    QList<QJsonObject> employees_list;
    QFile goods_file;
};

#endif // SHOP_SHOW_H
