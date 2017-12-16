#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500, 500);
    list = new QListWidget(this);

    btn = new QPushButton(this);
    btn->setText("Action");
    connect(btn, SIGNAL(clicked()), this, SLOT(showList()));

    grid = new QGridLayout(this);
    grid->addWidget(list, 0, 0);
    grid->addWidget(btn, 1, 0);
}

void MainWindow::showList()
{
    DeviceManager device;

    device.getDeviceList();
    //device.getVendorList();

    if(list->count())
        list->clear();

    for(int i = 0; i < device.getSize(); i++)
    {
        cout << device.getList()[i].hw_path << endl;
        list->addItem(QString(device.getList()[i].full_info));
    }
}

void MainWindow::disconnectDevice()
{

}

void MainWindow::connectDevice()
{

}

