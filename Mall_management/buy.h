#ifndef BUY_H
#define BUY_H

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
    class Buy;
}

class Buy : public QMainWindow
{
    Q_OBJECT

public:
    explicit Buy(QWidget* parent = nullptr);
    ~Buy();

private slots:
    void on_back_Button_clicked();

    void on_buy_Button_clicked();
public slots:
    void recv_account(QString account);
signals:
    void back_account(QString account);

private:
    Ui::Buy* ui;
    QList<QJsonObject> list;
    QFile goods_file;
    QFile goods_list_file;
    QList<QJsonObject> shop_list;
    QString account;

};

#endif // BUY_H
