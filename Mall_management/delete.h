#ifndef DELETE_H
#define DELETE_H

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
    class Delete;
}

class Delete : public QMainWindow
{
    Q_OBJECT

public:
    explicit Delete(QWidget* parent = nullptr);
    ~Delete();
    void delete_info();

private slots:
    void on_delete_Button_clicked();

    void on_back_Button_clicked();

    void on_info_Widget_itemDoubleClicked(QListWidgetItem* item);

private:
    Ui::Delete* ui;
    QList<QJsonObject> employees_list;
    QFile account_file;
};

#endif // DELETE_H
