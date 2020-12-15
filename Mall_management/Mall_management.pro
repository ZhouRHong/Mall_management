#-------------------------------------------------
#
# Project created by QtCreator 2020-11-14T09:54:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mall_management
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        add.cpp \
        admin.cpp \
        buy.cpp \
        check.cpp \
        delete.cpp \
        employees_interface.cpp \
        goods.cpp \
        main.cpp \
        mainwindow.cpp \
        order.cpp \
        shop_show.cpp \
        staff.cpp

HEADERS += \
        add.h \
        admin.h \
        buy.h \
        check.h \
        delete.h \
        employees_interface.h \
        goods.h \
        mainwindow.h \
        order.h \
        shop_show.h \
        staff.h

FORMS += \
        add.ui \
        admin.ui \
        buy.ui \
        check.ui \
        delete.ui \
        employees_interface.ui \
        goods.ui \
        mainwindow.ui \
        order.ui \
        shop_show.ui \
        staff.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res1.qrc
