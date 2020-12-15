#ifndef EMPLOYEES_INTERFACE_H
#define EMPLOYEES_INTERFACE_H

#include <QMainWindow>

namespace Ui
{
    class Employees_interface;
}

class Employees_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Employees_interface(QWidget* parent = nullptr);
    ~Employees_interface();

private slots:
    void on_pushButton_2_clicked();

    void on_customer_Button_clicked();

    void on_goods_Button_clicked();
public slots:
    void recv(QString account);
    void recv_back_account(QString account);

signals:
    void send_account(QString name);

private:
    Ui::Employees_interface* ui;
};

#endif // EMPLOYEES_INTERFACE_H
