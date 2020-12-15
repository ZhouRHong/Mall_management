#ifndef GOODS_H
#define GOODS_H

#include <QMainWindow>

namespace Ui
{
    class Goods;
}

class Goods : public QMainWindow
{
    Q_OBJECT

public:
    explicit Goods(QWidget* parent = nullptr);
    ~Goods();

private slots:
    void on_back_Button_clicked();

    void on_procurement_Button_clicked();

    void on_check_Button_clicked();

private:
    Ui::Goods* ui;
};

#endif // GOODS_H
