#ifndef ADMIN_SHOW_H
#define ADMIN_SHOW_H

#include <QWidget>

namespace Ui
{
    class Admin_show;
}

class Admin_show : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_show(QWidget* parent = nullptr);
    ~Admin_show();

private slots:
    void on_employees_Button_clicked();

    void on_goods_Button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Admin_show* ui;
};

#endif // ADMIN_SHOW_H
