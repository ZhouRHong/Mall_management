#ifndef ADD_H
#define ADD_H

#include <QMainWindow>
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
    class Add;
}

class Add : public QMainWindow
{
    Q_OBJECT

public:
    explicit Add(QWidget* parent = nullptr);
    ~Add();

private slots:
    void on_ok_Button_clicked();

    void on_back_Button_clicked();

private:
    Ui::Add* ui;
    QList<QJsonObject> employees_list;
    QFile account_file;
};

#endif // ADD_H
