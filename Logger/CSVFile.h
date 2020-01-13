class CSVFile
{
  private:
    char filename[64];

  public:
    CSVFile(const char *filename);
    ~CSVFile();

    bool addField(const char *field);
    bool nextLine();
};
