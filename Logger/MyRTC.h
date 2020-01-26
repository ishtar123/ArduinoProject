#pragma once
#include <Arduino.h>
#include <RTClib.h>

class MyRTC
{
    private:
        // millis()関数と同期
        RTC_Millis rtc;

    public:
        MyRTC();
        ~MyRTC();

        bool updateTime();
        bool getTime(char *buf, unsigned int buf_size);
};