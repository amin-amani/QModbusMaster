#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QSerialPortInfo>
#include "Modbus.h"
#include "Types.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#define MainBoardModbusID 1

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Modbus _modbus;
    QTimer _timer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




public slots:
    void ReadAllParameters();
private:
    Ui::MainWindow *ui;

signals:

private slots:
    void on_BtnOpenPort_clicked();
    void on_BtnRead_clicked();
    void on_BtnWrite_clicked();
    void on_BtnFeedRatio_clicked();
    void on_BtnLightIntensity_clicked();
    void on_BtnValveDuration_clicked();
    void on_BtnMainBoardID_clicked();
    void on_BtnFeederOnOff_clicked();
    void on_BtnTrigOnOff_clicked();
    void on_BtnPcOnOff_clicked();
    void on_BtnPcReset_clicked();
    void on_BtnLED_clicked();
    void on_BtnValveDelay_clicked();
    void on_BtnValve1_clicked();
    void on_BtnValve2_clicked();
    void on_BtnValve3_clicked();
    void on_BtnValve4_clicked();
    void on_BtnValve5_clicked();
    void on_BtnValve6_clicked();
    void on_BtnValve7_clicked();
    void on_BtnValve8_clicked();
    void on_BtnValve9_clicked();
    void on_BtnValve10_clicked();
    void on_BtnValve11_clicked();
};
#endif // MAINWINDOW_H
