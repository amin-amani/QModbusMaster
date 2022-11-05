#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
_modbus.Init("/dev/ttyUSB0",115200);
qDebug()<<_modbus.ConnectToDevice();
_modbus.ReadValTest();

}

MainWindow::~MainWindow()
{
    delete ui;
}

