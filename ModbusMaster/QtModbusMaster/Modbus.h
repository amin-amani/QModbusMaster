#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QModbusDataUnit>
#include <QModbusClient>
#include <QSerialPort>
#include <QModbusServer>
#include <QModbusRtuSerialMaster>
#include <QModbusRtuSerialSlave>
#include <QtSerialBus/QModbusRtuSerialMaster>
class Modbus : public QObject
{
    Q_OBJECT
    QModbusClient *modbusDevice;
    QByteArray _replay;
    QModbusDataUnit ReadRequest(int startAddress, int numberOfEntries, QModbusDataUnit::RegisterType type) const;
public:
    explicit Modbus(QObject *parent = nullptr);
    void Init(QString portName,int baudRate);
    bool ConnectToDevice();

    bool WaitDataReceive(int timeout);
    void ReadValTest();
public slots:
    void ReadyRead();
    void ModBusErrorHandler(QModbusDevice::Error error);
signals:
        void ModbusReadyRead();

};

#endif // MODBUS_H
