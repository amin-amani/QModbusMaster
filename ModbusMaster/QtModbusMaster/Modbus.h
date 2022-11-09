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
#include "Types.h"
#include "writeregistermodel.h"
class Modbus : public QObject
{
    Q_OBJECT
    QModbusClient *modbusDevice=nullptr;
    QByteArray _replay;
    QModbusDataUnit ReadRequest(int startAddress, int numberOfEntries, QModbusDataUnit::RegisterType type) const;
    QModbusDataUnit WriteRequest(int startAddress, int numberOfEntries, QModbusDataUnit::RegisterType type) const;
public:
    explicit Modbus(QObject *parent = nullptr);
    void Init(QString portName,int baudRate);
    bool ConnectToDevice();
    bool IsConnected();

    bool WaiteDataReceive(int timeout);
    void ReadValue();
    uint16_t ReadValue(MainBoardHoldings InputParameters, int deviceID);
    uint16_t ReadValue(MainBoardCoils InputParameters , int deviceID);
    void WriteParameter(int parameter, uint16_t value, int deviceID, QModbusDataUnit::RegisterType registerType) throw(std::runtime_error);
    uint16_t ReadValue(RealyAlarmInputs value, int deviceID);
    uint16_t ReadValue(RealyAlarmHoldings value, int deviceID);
    uint16_t ReadValue(RealyAlarmCoils value, int deviceID);
    uint16_t ReadValue(RealyAlarmDiscreteInput value, int deviceID);
    bool DisconnectFromDevice();
public slots:
    void ReadyRead();
    void ModBusErrorHandler(QModbusDevice::Error error);
signals:
        void ModbusReadyRead();

};

#endif // MODBUS_H
