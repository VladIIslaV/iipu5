#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "stdafx.h"
#include "devicemanager.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    QListWidget *list;
    QPushButton *btn;
    QPushButton *btn1;
    QPushButton *btn2;
    QGridLayout *grid;
    DeviceManager device;
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void showList();

    void onDevice();
    void offDevice();
};

#endif // MAINWINDOW_H
