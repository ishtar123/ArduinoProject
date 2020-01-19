#pragma once
#include "TextFile.h"

class INIFile : public TextFile
{
    public:
        INIFile(const char *filename);
        ~INIFile();
        bool getLine(const int row, char *line, const unsigned int bufsize, bool clearEscape=false);
        bool getParam(const char *section, const char *param, char *buf);
};