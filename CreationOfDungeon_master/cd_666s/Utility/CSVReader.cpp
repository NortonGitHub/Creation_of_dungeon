#include "CSVReader.h"

using namespace std;

CSVReader::CSVReader()
{
}


size_t CSVReader::GetLineSize(const std::string &fileName, int lineNum)
{
    // �Z�[�u�t�@�C���I�[�v��
    fstream fs(fileName);
    if (!fs.is_open())
        return 0;
    
    string str;
    size_t lineSize = 0;
    
    //�ǂݏ��߂ƂȂ镶����̎w�肪�����
    for (int i=0; i<=lineNum; ++i)
    {
        //�s���܂� "," ��؂�œǂݍ���
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);

            //�ǂݍ��񂾐������J�E���g
            lineSize++;
        }
    }
    
    //�t�@�C�������
    fs.close();
    return lineSize;
}


size_t CSVReader::GetLineNum(const std::string &fileName)
{
    // �Z�[�u�t�@�C���I�[�v��
    fstream fs(fileName);
    if (!fs.is_open())
        return 0;
    
    string str;
    size_t lineNum = 0;
    
    while (!fs.eof())
    {
        //�s���܂� "," ��؂�œǂݍ���
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //���s���܂񂾕������ǂݍ��񂾂�
            if (readBR)
                lineNum++;
        }
    }
    
    //�Z�[�u�t�@�C�������
    fs.close();
    return lineNum;
}


void CSVReader::Read(const string &fileName, DataArray &dataArray, const std::string &seekString)
{
    // �Z�[�u�t�@�C���I�[�v��
    fstream fs(fileName);
    if (!fs.is_open())
        return;
    
    string str;
    
    //�ǂݏ��߂ƂȂ镶����̎w�肪�����
    if (seekString != "")
    {
        //�ړI�̕�����ɓ�����܂œǂݔ�΂�
        while (str != seekString)
        {
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find(seekString);
            if (it != basic_string<char>::npos)
            {
                str.erase(0, it);
                
                //�����܂ŗ����
                //str �� �w�W�ƂȂ镶���� ��ǂݍ���ł���̂ł����ԂȂ̂�
                //��������[�h����
                dataArray.push_back(str);
                break;
            }
        }
    }
    
    while (!fs.eof())
    {
        //�s���܂� "," ��؂�œǂݍ���
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //���s���܂񂾕������ǂݍ��񂾂�
            if (readBR)
            {
                //���s�����2�����B
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());
                
                dataArray.push_back(cut);
            }
            
            dataArray.push_back(str);
        }
    }
    
    //�Z�[�u�t�@�C�������
    fs.close();
}


void CSVReader::Read(const string &fileName, DataArray &dataArray, const int ignoreLine)
{
    // �Z�[�u�t�@�C���I�[�v��
    fstream fs(fileName);
    if (!fs.is_open())
        return;
    
    string str;
    
    //�ǂݏ��߂ƂȂ镶����̎w�肪�����
    for (int i=0; i<ignoreLine; ++i)
    {
        //�s���܂� "," ��؂�œǂݍ���
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //���s���܂񂾕������ǂݍ��񂾂�
            if (readBR)
            {
                //���s�����2�����B
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());

                //���s����ɕ����������Ƃ̃f�[�^�ɉ��s���܂܂�Ă�����
                auto it2 = str.find("\n");
                if (it2 != basic_string<char>::npos)
                    str = str.substr(0, it2);

                //���s�̒���̕������ǉ�
                if (ignoreLine-1 == i)
                    dataArray.push_back(str);
            }
        }
    }
    
    while (!fs.eof())
    {
        //�s���܂� "," ��؂�œǂݍ���
        bool readBR = false;
        
        while (!readBR)
        {
            //read
            getline(fs.seekg(0, ios_base::cur), str, ',');
            
            auto it = str.find("\n");
            readBR = (it != basic_string<char>::npos);
            
            //���s���܂񂾕������ǂݍ��񂾂�
            if (readBR)
            {
                //���s�����2�����B
                string cut = str.substr(0, it);
                str = str.substr(it + 1, str.size());
                if (cut != "")
                    dataArray.push_back(cut);
                else
                    break;
            }
            
            //�󕶎��`�F�b�N
            if (str != "")
                dataArray.push_back(str);
        }
    }
    
    //�Z�[�u�t�@�C�������
    fs.close();
}


CSVReader::~CSVReader()
{
}
