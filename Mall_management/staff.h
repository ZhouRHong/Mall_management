#ifndef STAFF_H
#define STAFF_H

#include <QMainWindow>
#include "add.h"
namespace Ui
{
    class Staff;
}

class Staff : public QMainWindow
{
    Q_OBJECT

public:
    explicit Staff(QWidget* parent = nullptr);
    ~Staff();

private slots:
    void on_add_Button_clicked();

    void on_delet_Button_clicked();

    void on_backe_Button_clicked();

private:
    Ui::Staff* ui;

};

#endif // STAFF_H
