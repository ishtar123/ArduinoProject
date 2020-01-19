#include <SD.h>
#include <MsTimer2.h>
#include "INIFile.h"
#include "CSVFile.h"
#include "TextFile.h"

#define SDPINNO 10

void setup() {
    char buf[64];

    Serial.begin(9600);
    while(!Serial) {}

    SD.begin(SDPINNO);

    INIFile myFile("config/setting.ini");
    myFile.getParam("[setting]", "param1=", buf);
    Serial.println(buf);

    // タイマーを設定
    MsTimer2::set(500, timer_tick);
    MsTimer2::start();
}

void loop() {
  
}

void timer_tick(){
    unsigned long time;

    time = millis();

    CSVFile mycsv("data.csv");

    mycsv.writeLineByFormat("%lu,%d", time, analogRead(0));
}
