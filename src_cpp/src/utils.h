#ifndef GUARD_UTILS_H
#define GUARD_UTILS_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "teestream.h"

using std::vector;
using std::map;
using std::string;
using std::ifstream;

class CCSVParser{
public:
    char Delimiter;
    bool IsFirstLineHeader;
    // for DataHub CSV files
    bool m_bSkipFirstLine;
    bool m_bDataHubSingleCSVFile;
    bool m_bLastSectionRead;
    
    std::ifstream inFile;
    std::string mFileName;
    std::string m_DataHubSectionName;
    std::string SectionName;
    
    std::vector<std::string> LineFieldsValue;
    std::vector<int> LineIntegerVector;
    std::vector<std::string> Headers;
    std::map<std::string, int> FieldsIndices;

    CCSVParser() : Delimiter{ ',' }, IsFirstLineHeader{ true }, m_bSkipFirstLine{ false }, m_bDataHubSingleCSVFile{ false }, m_bLastSectionRead{ false }
    {
    }

    ~CCSVParser()
    {
        if (inFile.is_open()) 
            inFile.close();
    }

    // inline member functions
    std::vector<std::string> GetHeaderVector() 
    {
        return Headers;
    }
    void CloseCSVFile()
    {
        inFile.close();
    }

    void ConvertLineStringValueToIntegers();
    bool OpenCSVFile(std::string fileName, bool b_required);
    bool ReadRecord();
    bool ReadSectionHeader(std::string s);
    bool ReadRecord_Section();
    std::vector<std::string> ParseLine(std::string line);
    template <class T> bool GetValueByFieldName(std::string field_name, T& value, bool required_field = true, bool NonnegativeFlag = true);
    bool GetValueByFieldName(std::string field_name, std::string& value, bool required_field = true);
};

// utilities functions
teestream& dtalog();
void g_ProgramStop();

void fopen_ss(FILE** file, const char* fileName, const char* mode);
float g_read_float(FILE* f);

vector<string> split(const string &s, const string &seperator);
vector<float> g_time_parser(string str);
string g_time_coding(float time_stamp);
int g_ParserIntSequence(std::string str, std::vector<int>& vect);

#endif