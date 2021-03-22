/* Portions Copyright 2019 Xuesong Zhou
 *
 * If you help write or modify the code, please also list your names here.
 * The reason of having Copyright info here is to ensure all the modified version, as a whole, under the GPL
 * and further prevent a violation of the GPL.
 *
 * More about "How to use GNU licenses for your own software"
 * http://www.gnu.org/licenses/gpl-howto.html 
 */

#ifndef GUARD_UTILS_H
#define GUARD_UTILS_H

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include "teestream.h"

// utilities functions
teestream& dtalog();
void g_ProgramStop();

void fopen_ss(FILE** file, const char* fileName, const char* mode);
float g_read_float(FILE* f);

std::vector<std::string> split(const std::string& s, const std::string& seperator);
int g_ParserIntSequence(std::string str, std::vector<int>& vect);

std::vector<float> g_time_parser(std::string str);
std::string g_time_coding(float time_stamp);

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
    bool GetValueByFieldName(std::string field_name, std::string& value, bool required_field = true);
    template <class T> bool GetValueByFieldName(std::string field_name, T& value, bool required_field = true, bool NonnegativeFlag = true);
};

// Peiheng, 03/22/21, to avoid implicit instantiations in flash_dta.cpp and main_api.cpp for this template function only
// all the other non-inline functions are implemented in utils.cpp
template <class T> 
bool CCSVParser::GetValueByFieldName(std::string field_name, T& value, bool required_field, bool NonnegativeFlag)
{
    if (FieldsIndices.find(field_name) == FieldsIndices.end())
    {
        if (required_field)
        {
            dtalog() << "Field " << field_name << " in file " << mFileName << " does not exist. Please check the file." << std::endl;
            g_ProgramStop();
        }
        return false;
    }
    else
    {
        if (LineFieldsValue.size() == 0)
        {
            return false;
        }

        int size = (int)(LineFieldsValue.size());
        if (FieldsIndices[field_name] >= size)
        {
            return false;
        }

        std::string str_value = LineFieldsValue[FieldsIndices[field_name]];

        if (str_value.length() <= 0)
        {
            return false;
        }

        std::istringstream ss(str_value);

        T converted_value;
        ss >> converted_value;

        if (/*!ss.eof() || */ ss.fail())
        {
            return false;
        }

        if (required_field)
        {
            if(NonnegativeFlag)
            { 
                if (converted_value < 0)
                    converted_value = 0;
            }
        }

        value = converted_value;
        return true;
    }
}

#endif