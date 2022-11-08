#ifndef TYPES_H
#define TYPES_H
enum class MainBoardHoldings
{
    FeederRatio=0,
    LightIntensity=1,
    ValveDuration=2,
    Valvedelay=3,
    MainBoardID=4

};
enum class MainBoardCoils
{
feederOneOff=0,
TrigOnOff=1,
PCOnOff=2,
PCReset=3,
LED=4,
Valve1=5,
Valve2=6,
Valve3=7,
Valve4=8,
Valve5=9,
Valve6=0x0A,
Valve7=0x0B,
Valve8=0x0C,
Valve9=0x0D,
Valve10=0x0E,
Valve11=0x0F
};
enum class RealyAlarmHoldings
{
CamBoxTempSetpoint=0,
ProcessBoxTempSetpoint=1,
differentialTemp=2,
ProcessBoxTempSensorSerNum=3,
CamBox1TempSensorSerNum=4,
CamBox2TempSensorSerNum=5
};
enum class RealyAlarmCoils
{
Relay1=0,
Relay2=1,
Relay3=2,
Relay4=3,
ModemRelay=4,
FanBox=5,
};
enum class RealyAlarmInputs
{
Pressuresensor=0,
ProcessorBoxTemperature=1,
Camera1Temperature=2,
Camera2Temperature=3

};
enum class RealyAlarmDiscreteInput
{
BoxSwitch=0,
CH1Switch=1,
CH2Switch=2
};

#endif // TYPES_H
