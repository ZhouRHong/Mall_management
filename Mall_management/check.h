#ifndef CHECK_H
#define CHECK_H

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
    class Check;
}

class Check : public QMainWindow
{
    Q_OBJECT

public:
    explicit Check(QWidget* parent = nullptr);
    ~Check();

private slots:
    void on_category_Button_clicked();

    void on_name_Button_clicked();

    void on_price_Button_clicked();

    void on_back_Button_clicked();

private:
    Ui::Check* ui;
    QList<QJsonObject> employees_list;
    QFile goods_file;
};

#endif // CHECK_H
