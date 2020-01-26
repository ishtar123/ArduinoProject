#include <SD.h>
#include <MsTimer2.h>
#include "INIFile.h"
#include "CSVFile.h"
#include "TextFile.h"
#include "MyRTC.h"

#define SDPINNO 10

CSVFile mycsv("data.csv");
MyRTC myrtc;
unsigned long timer = 0;

void setup() {
    char buf[64];

    Serial.begin(9600);
    while(!Serial) {}

    SD.begin(SDPINNO);

    INIFile myFile("config/setting.ini");
    myFile.getParam("[setting]", "param1=", buf);
    Serial.println(buf);
}

void loop() {
    char buf[64];
    if(millis() - timer >= 250)
    {
        timer = millis();
        //mycsv.writeLineByFormat("%lu,%d", millis(), analogRead(0));
        myrtc.getTime(buf, 64);
        Serial.println(buf);
    }
}