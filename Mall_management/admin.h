#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "staff.h"
namespace Ui
{
    class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget* parent = nullptr);
    ~Admin();

private slots:
    //void on_pushButton_clicked();

    void on_employees_Button_clicked();

    void on_goods_Button_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin* ui;

};

#endif // ADMIN_H
