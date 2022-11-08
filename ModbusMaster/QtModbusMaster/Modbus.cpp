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

bool Modbus::IsConnected()
{
    if(modbusDevice==nullptr)return false;
   if(modbusDevice->state()==QModbusDevice::State::ConnectedState)return true;
   return false;
}
//==========================================================================================================
uint16_t Modbus::ReadValue(MainBoardCoils InputParameters , int deviceID)
{
    auto *reply = modbusDevice->sendReadRequest(ReadRequest((int)InputParameters,1,QModbusDataUnit::RegisterType::Coils), deviceID);
    connect(reply, SIGNAL(finished()), this,SLOT( ReadyRead()));
    WaiteDataReceive(100);
    reply->deleteLater();
    if(_replay.count()<1)
    {
        qDebug()<<"read val error";
        return 0;
    }
    return _replay[0];
}
//==========================================================================================================

uint16_t Modbus::ReadValue(MainBoardHoldings InputParameters , int deviceID)
{
    auto *reply = modbusDevice->sendReadRequest(ReadRequest((int)InputParameters,1,QModbusDataUnit::RegisterType::HoldingRegisters), deviceID);
    connect(reply, SIGNAL(finished()), this,SLOT( ReadyRead()));
    WaiteDataReceive(100);
    reply->deleteLater();
    if(_replay.count()<1)
    {
        qDebug()<<"read val error";
        return 0;
    }
    return _replay[0];
}
//==========================================================================================================
bool Modbus::WaiteDataReceive(int timeout)
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
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply){
        return;}
    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        _replay.clear();
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                    .arg(QString::number(unit.value(i),unit.registerType() <= QModbusDataUnit::Coils ? 10 : 10));
            _replay.append(unit.value(i));
        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        qDebug()<<(tr("Read response error: %1 (Mobus exception: 0x%2)").
                   arg(reply->errorString()).
                   arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    }
    else
    {

    }
    emit ModbusReadyRead();
}
//==========================================================================================================
QModbusDataUnit Modbus::ReadRequest(int startAddress , int numberOfEntries,QModbusDataUnit::RegisterType type) const
{

    const auto table = static_cast<QModbusDataUnit::RegisterType> (type);
    Q_ASSERT(startAddress >= 0 && startAddress <= 15);
    // do not go beyond 10 entries
    // qMin(ui->readSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
//==============================================================================
QModbusDataUnit Modbus::WriteRequest(int startAddress , int numberOfEntries,QModbusDataUnit::RegisterType type) const
{
    const auto table = static_cast<QModbusDataUnit::RegisterType>(type); //(QModbusDataUnit::HoldingRegisters);
    Q_ASSERT(startAddress >= 0 && startAddress <= 15);
    // do not go beyond 10 entries

    //  int numberOfEntries =9;// qMin(ui->readSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
//==============================================================================

void Modbus::WriteParameter(int parameter,uint16_t value,int deviceID,
                            QModbusDataUnit::RegisterType registerType)throw(std::runtime_error)
{


    if (modbusDevice==nullptr)return;
//        throw std::runtime_error("Modbus not connected") ;
    WriteRegisterModel *writeModel = new WriteRegisterModel(this);
    writeModel->setStartAddress(parameter);
    writeModel->setNumberOfValues(QString::number(deviceID));


    QModbusDataUnit writeUnit = WriteRequest(parameter,1,registerType);
    QModbusDataUnit::RegisterType table = writeUnit.registerType();
    writeUnit.setValue(0,value);
    modbusDevice->setTimeout(100);

if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, deviceID)) {


        if (!reply->isFinished()) {
            //            qDebug()<<"isFinished";
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    //            statusBar()->showMessage(tr("Write response error: %1 (Mobus exception: 0x%2)")
                    //                .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                    //                5000);
                    qDebug()<<"Write response error";
                } else if (reply->error() != QModbusDevice::NoError) {
                    //            statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
                    //                arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
                    qDebug()<<"QModbusDevice::NoError";
                }
                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            qDebug()<<"broadcast replies return immediately";
            reply->deleteLater();
        }
    } else {
        qDebug()<<tr("Write error: ") << modbusDevice->errorString();
    }
}
//==============================================================================
void Modbus::ModBusErrorHandler(QModbusDevice::Error error)
{

qDebug()<<error;

}
