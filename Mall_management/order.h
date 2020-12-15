#ifndef ORDER_H
#define ORDER_H

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
    class Order;
}

class Order : public QMainWindow
{
    Q_OBJECT

public:
    explicit Order(QWidget* parent = nullptr);
    ~Order();

private slots:
    void on_back_Button_clicked();

    void on_fast_Button_clicked();

    void on_category_Button_clicked();

    void on_name_Button_clicked();

    void on_price_Button_clicked();
public slots:
    void recv(QString account);
signals:
    void back_account(QString account);

private:
    Ui::Order* ui;
    QFile goods_list_file;
    QList<QJsonObject> shop_list;
    QString account;
};

#endif // ORDER_H
