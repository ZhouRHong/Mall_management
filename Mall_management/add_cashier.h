#ifndef ADD_CASHIER_H
#define ADD_CASHIER_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtDebug>
#include <QMessageBox>
#include <synchapi.h>
#include <QTimer>
#include <admin_show.h>
namespace Ui
{
    class Add_cashier;
}

class Add_cashier : public QWidget
{
    Q_OBJECT

public:
    explicit Add_cashier(QWidget* parent = nullptr);
    ~Add_cashier();

private slots:
    void on_back_Button_clicked();

    void on_ok_Button_clicked();

private:
    Ui::Add_cashier* ui;
    QList<QJsonObject> employees_list;
    QFile account_file;
};

#endif // ADD_CASHIER_H
