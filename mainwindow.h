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
    QGridLayout *grid;
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void showList();
    void disconnectDevice();
    void connectDevice();
};

#endif // MAINWINDOW_H
