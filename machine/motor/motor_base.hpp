#pragma once

class MotorBase
{
public:
    //pwmで回す
    void setPwm();

    //Dutyで回す
    void setDuty();

    //速度制御（rpm）
    void setTgtAngVel();

    //位置制御（rad）
    void setTgtAng();

};
