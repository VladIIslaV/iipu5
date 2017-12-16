#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500, 500);
    list = new QListWidget(this);

    btn = new QPushButton(this);
    btn->setText("Release");
    connect(btn, SIGNAL(clicked()), this, SLOT(showList()));

    btn1 = new QPushButton(this);
    btn1->setText("Off");
    connect(btn1, SIGNAL(clicked()), this, SLOT(offDevice()));

    btn2 = new QPushButton(this);
    btn2->setText("On");
    connect(btn2, SIGNAL(clicked()), this, SLOT(onDevice()));

    grid = new QGridLayout(this);
    grid->addWidget(list, 0, 0, 1, 3);
    grid->addWidget(btn, 1, 0);
    grid->addWidget(btn1, 1, 1);
    grid->addWidget(btn2, 1, 2);
}

void MainWindow::showList()
{
    device.getDeviceList();
    device.getDriverPath();

    if(list->count())
        list->clear();

    for(int i = 0; i < device.getSize(); i++)
    {
        list->addItem(QString(device.getList()[i].full_info));
    }
}

void MainWindow::onDevice()
{
    if(list->count()){
        device.onDevice(list->currentRow());
        cout << "### " << list->currentRow() << endl;
    }
}

void MainWindow::offDevice()
{
    if(list->count()){
        device.offDevice(list->currentRow());
        cout << "### " << list->currentRow() << endl;
    }
}


