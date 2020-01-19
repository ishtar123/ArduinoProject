#pragma once
#include <Arduino.h>
#include <SD.h>

class TextFile
{
    private:
        char *filename = nullptr;
        File file;
        bool isFileOpen = false;

        bool open(uint8_t mode = FILE_READ);
        char getChar();
        bool close();
    
    public:
        TextFile(const char *filename);
        ~TextFile();
        
        bool writeLine(const char *line);
        bool readLine(const int row, char *line, unsigned int bufsize);

        template <typename... Args>
        bool writeLineByFormat(const char *fmt, Args... args)
        {
            char line[256];
            sprintf(line, fmt, args...);
            
            return this->writeLine(line);
        };
};

