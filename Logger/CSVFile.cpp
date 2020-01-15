#include "CSVFile.h"
#include <Arduino.h>
#include <SD.h>

CSVFile::CSVFile(const char *filename){
    strcpy(this->filename, filename);
}

CSVFile::~CSVFile(){
}

bool CSVFile::addField(const char *field){
    File file;

  // ファイルオープン
    file = SD.open(this->filename, FILE_WRITE);
    if(!file){
        Serial.println("CSVFile::addField\nFile open failed.");
        Serial.println(this->filename);
        return false;
    }

    // 書き込み
    file.print(field);
    file.print(",");

    file.close();

    return true;
}

bool CSVFile::nextLine(){
    File file;

    // ファイルオープン
    file = SD.open(this->filename, FILE_WRITE);
    if(!file){
        Serial.println("CSVFile::nextLine\nFile open failed.");
        Serial.println(this->filename);
        return false;
    }

    // 改行書き込み
    file.println("");

    file.close();

    return true;
}
