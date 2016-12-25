#ifndef CSV_READER_H
#define CSV_READER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/*
	CSVファイルの読み込みと
	データストリームを行う
 */


typedef std::vector<std::string> DataArray;

class CSVReader
{
    
public:
    CSVReader();
    ~CSVReader();
    
    size_t GetLineSize(const std::string &fileName, int lineNum);
    size_t GetLineNum(const std::string &fileName);
    
    void Read(const std::string &fileName, DataArray &dataArray, const std::string &seekString = "");
    void Read(const std::string &fileName, DataArray &dataArray, const int ignoreLineNum);
    
private:
    std::stringstream ss;
};

#endif