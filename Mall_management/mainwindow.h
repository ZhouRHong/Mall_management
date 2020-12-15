#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtDebug>
#include <QMessageBox>
#include <synchapi.h>
#include <QTimer>
#include "admin.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_management_Button_clicked();

    void on_employees_Button_clicked();
signals:
    void send(QString account);
private:
    Ui::MainWindow* ui;
    Admin* admin;
    QList<QJsonObject> employees_list;
};

#endif // MAINWINDOW_H
