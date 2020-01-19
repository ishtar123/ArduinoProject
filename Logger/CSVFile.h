#pragma once
#include "TextFile.h"

class CSVFile : public TextFile
{
    public:
        CSVFile(const char *filename);
        ~CSVFile();
};