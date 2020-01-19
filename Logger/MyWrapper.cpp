#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

namespace MyWrapper
{
    RTC_DS1307 RTC;

    void initRTC()
    {
        Wire.begin();
        MyWrapper::RTC.begin();
        if (! MyWrapper::RTC.isrunning()) {
            Serial.println("RTC is NOT running!");
            // following line sets the RTC to the date & time this sketch was compiled
            MyWrapper::RTC.adjust(DateTime(__DATE__, __TIME__));
        }
    }

    void getTimeFromRTC(char *buf, const int buf_size)
    {
        DateTime now = MyWrapper::RTC.now(); 
        sprintf(buf, "%hu/%hu/%hu %hu:%hu:%hu", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    }
}