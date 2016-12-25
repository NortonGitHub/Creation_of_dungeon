#include "CSVReader.h"

using namespace std;

CSVReader::CSVReader()
{
}


size_t CSVReader::GetLineSize(const std::string &fileName, int lineNum)
{
    // セーブファイルオープン
    fstream fs(fileName);
    if (!fs.is_open())
        return 0;
    
    string str;
    size_t lineSize = 0;
    
    //読み初めとなる文字列の指定があれば
    for (int i=0; i<=lineNum; ++i)
    {
        //行末まで "," 区切りで読み込む
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);

            //読み込んだ数だけカウント
            lineSize++;
        }
    }
    
    //ファイルを閉じる
    fs.close();
    return lineSize;
}


size_t CSVReader::GetLineNum(const std::string &fileName)
{
    // セーブファイルオープン
    fstream fs(fileName);
    if (!fs.is_open())
        return 0;
    
    string str;
    size_t lineNum = 0;
    
    while (!fs.eof())
    {
        //行末まで "," 区切りで読み込む
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //改行を含んだ文字列を読み込んだら
            if (readBR)
                lineNum++;
        }
    }
    
    //セーブファイルを閉じる
    fs.close();
    return lineNum;
}


void CSVReader::Read(const string &fileName, DataArray &dataArray, const std::string &seekString)
{
    // セーブファイルオープン
    fstream fs(fileName);
    if (!fs.is_open())
        return;
    
    string str;
    
    //読み初めとなる文字列の指定があれば
    if (seekString != "")
    {
        //目的の文字列に当たるまで読み飛ばす
        while (str != seekString)
        {
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find(seekString);
            if (it != basic_string<char>::npos)
            {
                str.erase(0, it);
                
                //ここまで来ると
                //str に 指標となる文字列 を読み込んであるのである状態なので
                //それをロードする
                dataArray.push_back(str);
                break;
            }
        }
    }
    
    while (!fs.eof())
    {
        //行末まで "," 区切りで読み込む
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //改行を含んだ文字列を読み込んだら
            if (readBR)
            {
                //改行を基準に2分割。
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());
                
                dataArray.push_back(cut);
            }
            
            dataArray.push_back(str);
        }
    }
    
    //セーブファイルを閉じる
    fs.close();
}


void CSVReader::Read(const string &fileName, DataArray &dataArray, const int ignoreLine)
{
    // セーブファイルオープン
    fstream fs(fileName);
    if (!fs.is_open())
        return;
    
    string str;
    
    //読み初めとなる文字列の指定があれば
    for (int i=0; i<ignoreLine; ++i)
    {
        //行末まで "," 区切りで読み込む
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //改行を含んだ文字列を読み込んだら
            if (readBR)
            {
                //改行を基準に2分割。
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());

                //改行を基準に分割したあとのデータに改行が含まれていたら
                auto it2 = str.find("\n");
                if (it2 != basic_string<char>::npos)
                    str = str.substr(0, it2);

                //改行の直後の文字列を追加
                if (ignoreLine-1 == i)
                    dataArray.push_back(str);
            }
        }
    }
    
    while (!fs.eof())
    {
        //行末まで "," 区切りで読み込む
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //改行を含んだ文字列を読み込んだら
            if (readBR)
            {
                //改行を基準に2分割。
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());
                if (cut != "")
                    dataArray.push_back(cut);
                else
                    break;
            }
            
            //空文字チェック
            if (str != "")
                dataArray.push_back(str);
        }
    }
    
    //セーブファイルを閉じる
    fs.close();
}


CSVReader::~CSVReader()
{
}
