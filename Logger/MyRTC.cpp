#include "MyRTC.h"
#include <Arduino.h>
#include <Wire.h>

MyRTC::MyRTC()
{
    DateTime dt;

    // rtcを初期化
    Wire.begin();
    this->rtc.begin(dt);
}

MyRTC::~MyRTC()
{
}

bool MyRTC::updateTime()
{

}

bool MyRTC::getTime(char *buf, unsigned int buf_size)
{
    DateTime now = this->rtc.now(); 
    sprintf(buf, "%hu/%hu/%hu %hu:%hu:%hu.%hu", now.year(), now.month(), now.day(),
                                                now.hour(), now.minute(), now.second(), millis() % 1000);
}