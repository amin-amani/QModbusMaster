#include "Modbus.h"
//==========================================================================================================
Modbus::Modbus(QObject *parent) : QObject(parent)
{

}
//==========================================================================================================
void Modbus::Init(QString portName, int baudRate)
{
      modbusDevice = new QModbusRtuSerialMaster(this);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portName);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,baudRate);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);
    connect(modbusDevice,SIGNAL(errorOccurred(QModbusDevice::Error)),this,SLOT(ModBusErrorHandler(QModbusDevice::Error)));

}
//==========================================================================================================

bool Modbus::ConnectToDevice()
{
    return  modbusDevice->connectDevice();
}
//==========================================================================================================

void Modbus::ReadValTest()
{
    qDebug()<<"=================================================";
    int InputParameters =4;
    int deviceID=1;
    auto *reply = modbusDevice->sendReadRequest(ReadRequest(InputParameters,1,QModbusDataUnit::RegisterType::InputRegisters), deviceID);
    connect(reply, SIGNAL(finished()), this,SLOT( ReadyRead()));

        WaitDataReceive(100);
        reply->deleteLater();
        if(_replay.count()<1)
            qDebug()<<"read val error";
        qDebug()<<_replay[0];

}
//==========================================================================================================
bool Modbus::WaitDataReceive(int timeout)
{
    QEventLoop q;
    QTimer tT;
    tT.setSingleShot(true);
    connect(&tT, SIGNAL(timeout()), &q, SLOT(quit()));
    connect(this, SIGNAL(ModbusReadyRead()), &q, SLOT(quit()));
    tT.start(timeout);
    q.exec();
    if(tT.isActive())
    {

        tT.stop();
        return true;
    }
    else
    {

        return false;
    }


}

//==========================================================================================================
void Modbus::ReadyRead()
{
    // QMutexLocker locker(&lock);
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        _replay.clear();
        for (uint i = 0; i < unit.valueCount(); i++) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                    .arg(QString::number(unit.value(i),
                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 10));

            _replay.append(unit.value(i));
            //            qDebug()<<entry;
        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        qDebug()<<(tr("Read response error: %1 (Mobus exception: 0x%2)").
                   arg(reply->errorString()).
                   arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else {

    }
    emit ModbusReadyRead();

}
//==========================================================================================================
QModbusDataUnit Modbus::ReadRequest(int startAddress , int numberOfEntries,QModbusDataUnit::RegisterType type) const
{

    const auto table = static_cast<QModbusDataUnit::RegisterType> (type);
    Q_ASSERT(startAddress >= 0 && startAddress < 15);
    // do not go beyond 10 entries
    // qMin(ui->readSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
//==============================================================================
void Modbus::ModBusErrorHandler(QModbusDevice::Error error)
{

qDebug()<<error;

}
