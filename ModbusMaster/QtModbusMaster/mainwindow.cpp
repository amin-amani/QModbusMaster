#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_timer,SIGNAL(timeout()),this, SLOT(ReadAllParameters()));
    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {
        //Their is some sorting to do for just list the port I want, with vendor Id & product Id
        ui->CmbPortName->addItem(port.portName());
        //ports.append(port.portName());

    }
}
//========================================================================================================
MainWindow::~MainWindow()
{
    delete ui;
}

//=================================================================================================
void MainWindow::WaitMs(int ms)
{

    QEventLoop q;
    QTimer tT;
    tT.setSingleShot(true);
    connect(&tT, SIGNAL(timeout()), &q, SLOT(quit()));
    tT.start(ms);
    q.exec();
    if(tT.isActive()){
        tT.stop();
    } else
    {

    }
}
//========================================================================================================
void MainWindow::ReadAllParameters()
{
    if(ui->BtnRead->text()=="Start Read")return;
 if(!_modbus.IsConnected())return;
    qDebug()<<"tick...";
//    QString temp= "Feeder Ratio = "+QString::number( _modbus.ReadValue(MainBoardHoldings::FeederRatio,MainBoardModbusID));
//    ui->LabFeederRatio->setText(temp);
//    temp= "Light Intensity = "+QString::number( _modbus.ReadValue(MainBoardHoldings::LightIntensity,MainBoardModbusID));
//    ui->LabLightIntensity->setText(temp);
//    temp= "Valve Duration = "+QString::number( _modbus.ReadValue(MainBoardHoldings::ValveDuration,MainBoardModbusID));
//    ui->LabValveDuration->setText(temp);
//    temp= "Valve Delay = "+QString::number( _modbus.ReadValue(MainBoardHoldings::Valvedelay,MainBoardModbusID));
//    ui->LabValveDelay->setText(temp);
//    temp= "Main Board ID = "+QString::number( _modbus.ReadValue(MainBoardHoldings::MainBoardID,MainBoardModbusID));
//    ui->LabMainBoardID->setText(temp);
//    temp= "Main Board LED = "+QString::number( _modbus.ReadValue(MainBoardCoils::LED,MainBoardModbusID));
//    ui->LabLED->setText(temp);
//    temp= "PC Reset = "+QString::number( _modbus.ReadValue(MainBoardCoils::PCReset,MainBoardModbusID));
//    ui->LabPcReset->setText(temp);
//    temp= "PC ON/OFF = "+QString::number( _modbus.ReadValue(MainBoardCoils::PCOnOff,MainBoardModbusID));
//    ui->LabPcOnOff->setText(temp);
//    temp= "Trig on/off = "+QString::number( _modbus.ReadValue(MainBoardCoils::TrigOnOff,MainBoardModbusID));
//    ui->LabTrigOnOff->setText(temp);

//    temp= "feeder One/Off = "+QString::number( _modbus.ReadValue(MainBoardCoils::feederOneOff,MainBoardModbusID));
//    ui->LabFeederOnOff->setText(temp);

//    QString temp= "Valve1 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve1,MainBoardModbusID));
//    ui->LabValve1->setText(temp);
//    temp= "Valve2 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve2,MainBoardModbusID));
//    ui->LabValve2->setText(temp);
//    temp= "Valve3 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve3,MainBoardModbusID));
//    ui->LabValve3->setText(temp);
//    temp= "Valve4 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve4,MainBoardModbusID));
//    ui->LabValve4->setText(temp);
//    temp= "Valve5 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve5,MainBoardModbusID));
//    ui->LabValve5->setText(temp);
//    temp= "Valve6 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve6,MainBoardModbusID));
//    ui->LabValve6->setText(temp);
//    temp= "Valve7 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve7,MainBoardModbusID));
//    ui->LabValve7->setText(temp);
//    temp= "Valve8 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve8,MainBoardModbusID));
//    ui->LabValve8->setText(temp);
//    temp= "Valve9 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve9,MainBoardModbusID));
//    ui->LabValve9->setText(temp);
//    temp= "Valve10 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve10,MainBoardModbusID));
//    ui->LabValve10->setText(temp);
//    temp= "Valve11 = "+QString::number( _modbus.ReadValue(MainBoardCoils::Valve11,MainBoardModbusID));
//    ui->LabValve11->setText(temp);

   QString  temp= "Differential Temp = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::DifferentialTemp,RelayAlarmModbusID));
    ui->LabDifferentialTemp->setText(temp);
    WaitMs(10);
    temp= "Process Box Temp Setpoint = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::ProcessBoxTempSetpoint,RelayAlarmModbusID));
    ui->LabProcessBoxTempSetpoint->setText(temp);
    WaitMs(10);
    temp= "CamBox Temp Setpoint = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::CamBoxTempSetpoint,RelayAlarmModbusID));
    ui->LabCamBoxTempSetpoint->setText(temp);
    WaitMs(10);
    temp= "CamBox1 Temp Sensor SerNum = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::CamBox1TempSensorSerNum,RelayAlarmModbusID));
    ui->LabCamBox1TempSensorSerNum->setText(temp);
    WaitMs(10);
    temp= "Cam Box2 Temp Sensor SerNum = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::CamBox2TempSensorSerNum,RelayAlarmModbusID));
    ui->LabCamBox2TempSensorSerNum->setText(temp);
    WaitMs(10);
    temp= "Process Box Temp Sensor SerNum = "+QString::number( _modbus.ReadValue(RealyAlarmHoldings::ProcessBoxTempSensorSerNum,RelayAlarmModbusID));
    ui->LabProcessBoxTempSensorSerNum->setText(temp);


    WaitMs(10);
    temp= "Relay1 = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::Relay1,RelayAlarmModbusID));
    ui->LabRelayAlarmRelay1->setText(temp);
    WaitMs(10);
    temp= "Relay2 = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::Relay2,RelayAlarmModbusID));
    ui->LabRelayAlarmRelay2->setText(temp);
    WaitMs(10);
    temp= "Relay3 = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::Relay3,RelayAlarmModbusID));
    ui->LabRelayAlarmRelay3->setText(temp);
    WaitMs(10);
    temp= "Relay4 = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::Relay4,RelayAlarmModbusID));
    ui->LabRelayAlarmRelay4->setText(temp);
    WaitMs(10);
    temp= "ModemRelay = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::ModemRelay,RelayAlarmModbusID));
    ui->LabRelayAlarmModemRelay->setText(temp);
    WaitMs(10);
    temp= "FanBox = "+QString::number( _modbus.ReadValue(RealyAlarmCoils::FanBox,RelayAlarmModbusID));
    ui->LabRelayAlarmFanBox->setText(temp);

    WaitMs(10);
    temp= "Pressuresensor = "+QString::number( _modbus.ReadValue(RealyAlarmInputs::Pressuresensor,RelayAlarmModbusID));
    ui->LabPressureSensor->setText(temp);
    WaitMs(10);
    temp= "Camera1Temperature = "+QString::number( _modbus.ReadValue(RealyAlarmInputs::Camera1Temperature,RelayAlarmModbusID));
    ui->LabCamera1Temperature->setText(temp);
    WaitMs(10);
    temp= "Camera2Temperature = "+QString::number( _modbus.ReadValue(RealyAlarmInputs::Camera2Temperature,RelayAlarmModbusID));
    ui->LabCamera2Temperature->setText(temp);
    WaitMs(10);
    temp= "ProcessorBoxTemperature = "+QString::number( _modbus.ReadValue(RealyAlarmInputs::ProcessorBoxTemperature,RelayAlarmModbusID));
    ui->LabProcessorBoxTemperature->setText(temp);


    WaitMs(10);
    temp= "BoxSwitch = "+QString::number( _modbus.ReadValue(RealyAlarmDiscreteInput::BoxSwitch,RelayAlarmModbusID));
    ui->LabBoxSwitch->setText(temp);

    WaitMs(10);
    temp= "CH1Switch = "+QString::number( _modbus.ReadValue(RealyAlarmDiscreteInput::CH1Switch,RelayAlarmModbusID));
    ui->LabCH1Switch->setText(temp);

    WaitMs(10);
    temp= "CH2Switch = "+QString::number( _modbus.ReadValue(RealyAlarmDiscreteInput::CH2Switch,RelayAlarmModbusID));
    ui->LabCH2Switch->setText(temp);

}
//========================================================================================================
void MainWindow::on_BtnOpenPort_clicked()
{
    if(ui->BtnOpenPort->text()=="Open")
    {
    _modbus.Init(ui->CmbPortName->currentText(),115200);

    if(_modbus.ConnectToDevice())
    {
               ui->BtnOpenPort->setText("Close");
               ui->CmbPortName->setEnabled(false);
    }

    return;
    }
    _modbus.Init(ui->CmbPortName->currentText(),115200);
      ui->BtnOpenPort->setText("Open");
    _modbus.DisconnectFromDevice();
      ui->CmbPortName->setEnabled(true);
}
//========================================================================================================
void MainWindow::on_BtnRead_clicked()
{
    if(!_modbus.IsConnected())return;
if(ui->BtnRead->text()=="Start Read")
{
ui->BtnRead->setText("Stop Read");
_timer.start(500);
    return;
}
ui->BtnRead->setText("Start Read");
_timer.stop();
}
//========================================================================================================
void MainWindow::on_BtnWrite_clicked()
{
static bool toggle=0;
toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::PCOnOff, toggle,1,QModbusDataUnit::RegisterType::Coils);
}
//========================================================================================================
void MainWindow::on_BtnFeedRatio_clicked()
{
static bool toggle=0;
toggle=!toggle;
_modbus.WriteParameter((int)MainBoardHoldings::FeederRatio, toggle,1,QModbusDataUnit::RegisterType::HoldingRegisters);

}
//========================================================================================================
void MainWindow::on_BtnLightIntensity_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardHoldings::LightIntensity, toggle,1,QModbusDataUnit::RegisterType::HoldingRegisters);

}
//========================================================================================================
void MainWindow::on_BtnValveDuration_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardHoldings::ValveDuration, toggle,1,QModbusDataUnit::RegisterType::HoldingRegisters);

}
//========================================================================================================
void MainWindow::on_BtnMainBoardID_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardHoldings::MainBoardID, toggle+1,1,QModbusDataUnit::RegisterType::HoldingRegisters);

}
//========================================================================================================
void MainWindow::on_BtnFeederOnOff_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::feederOneOff, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnTrigOnOff_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::TrigOnOff, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnPcOnOff_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::PCOnOff, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnPcReset_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::PCReset, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnLED_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::LED, toggle,1,QModbusDataUnit::RegisterType::Coils);
}
//========================================================================================================
void MainWindow::on_BtnValveDelay_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardHoldings::Valvedelay, toggle,1,QModbusDataUnit::RegisterType::HoldingRegisters);
}
//========================================================================================================
void MainWindow::on_BtnValve1_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve1, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve2_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve2, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve3_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve3, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve4_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve4, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve5_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve5, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve6_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve6, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve7_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve7, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve8_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve8, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve9_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve9, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve10_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve10, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================
void MainWindow::on_BtnValve11_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)MainBoardCoils::Valve11, toggle,1,QModbusDataUnit::RegisterType::Coils);

}
//========================================================================================================

void MainWindow::on_BtnDifferentialTemp_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmHoldings::DifferentialTemp, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::HoldingRegisters);

}


void MainWindow::on_BtnCamBox1TempSensorSerNum_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmHoldings::CamBox1TempSensorSerNum, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::HoldingRegisters);

}

void MainWindow::on_BtnCamBox2TempSensorSerNum_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmHoldings::CamBox2TempSensorSerNum, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::HoldingRegisters);

}

void MainWindow::on_BtnProcessBoxTempSetpoint_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmHoldings::ProcessBoxTempSetpoint, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::HoldingRegisters);

}

void MainWindow::on_BtnCamboxTempSetpoint_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmHoldings::CamBoxTempSetpoint, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::HoldingRegisters);

}

void MainWindow::on_BtnRelayAlarmRelay1_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::Relay1, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnRelayAlarmRelay2_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::Relay2, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnRelayAlarmRelay3_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::Relay3, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnRelayAlarmRelay4_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::Relay4, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnModemRelay_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::ModemRelay, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnFanBox_clicked()
{
    static bool toggle=0;
    toggle=!toggle;
    _modbus.WriteParameter((int)RealyAlarmCoils::FanBox, toggle,RelayAlarmModbusID,QModbusDataUnit::RegisterType::Coils);

}

void MainWindow::on_BtnProcessorBoxTemperature_clicked()
{

}

void MainWindow::on_BtnCH2Switch_clicked()
{

}
