#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Modbus.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Modbus _modbus;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:

private:
    Ui::MainWindow *ui;

signals:

};
#endif // MAINWINDOW_H
