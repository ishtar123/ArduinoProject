#include <SD.h>
#include <MsTimer2.h>
#include "INIFile.h"
#include "CSVFile.h"
#include "TextFile.h"
#include "MyWrapper.h"

#define SDPINNO 10

CSVFile mycsv("data.csv");
unsigned long timer = 0;

void setup() {
    char buf[64];

    Serial.begin(9600);
    while(!Serial) {}

    SD.begin(SDPINNO);

    INIFile myFile("config/setting.ini");
    myFile.getParam("[setting]", "param1=", buf);
    Serial.println(buf);

    MyWrapper::initRTC();
    MyWrapper::getTimeFromRTC(buf, 64);
}

void loop() {
    if(millis() - timer > 1000)
    {
        timer = millis();
        mycsv.writeLineByFormat("%lu,%d", millis(), analogRead(0));
    }
}