#include <SD.h>

class INIFile{
  private:
    char filename[64];
    
  public:
    INIFile(char *filename);
    ~INIFile();
    bool getLine(const int row, char *line, const unsigned int bufsize, bool clearEscape=false);
    bool getParam(const char *section, const char *param, char *buf);
    bool writeParam(char *str);
    bool hasSection(const char *section);

  public:
    static bool initSD();
};
