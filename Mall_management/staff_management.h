#ifndef STAFF_MANAGEMENT_H
#define STAFF_MANAGEMENT_H

#include <QWidget>

namespace Ui
{
    class Staff_management;
}

class Staff_management : public QWidget
{
    Q_OBJECT

public:
    explicit Staff_management(QWidget* parent = nullptr);
    ~Staff_management();

private slots:
    void on_add_Button_clicked();

    void on_backe_Button_clicked();

private:
    Ui::Staff_management* ui;
};

#endif // STAFF_MANAGEMENT_H
