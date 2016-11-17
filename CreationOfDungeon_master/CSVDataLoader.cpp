#include "CSVDataLoader.h"
#include <fstream>
#include <sstream>
#include "CharaBase.h"


CSVDataLoader::CSVDataLoader()
{
}


CSVDataLoader::~CSVDataLoader()
{
}

void CSVDataLoader::LoadMapCSV(std::vector<MapData> &map_data, int stagenum)
{
    std::string filename = "stage_" + stagenum;
    filename += ".csv";
    std::ifstream ifs(filename);
    if (!ifs) {
        return;
    }

    //csv�t�@�C����1�s���ǂݍ���
    std::string str;
    int now_row = 0;    //�s
    int now_column = 0; //��    

    while (!ifs.eof()) {
        std::string token;
        std::istringstream stream(str);

        now_column = 0;

        while (getline(stream, token, ',')) {
            //���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
            //���l�͕ϊ����K�v

            int temp = stoi(token); //stof(string str) : string��float�ɕϊ�
            map_data.push_back(MapData(now_column, now_row, temp));
            now_column++;
        }
        now_row++;
    }
}

/*
int,temp_i[]
         [0]: x
         [1]: y
         [2]: width
         [3]: height
str,temp_s  : UI_type_name
*/
void CSVDataLoader::LoadUICSV(std::vector<UIContent> &ui_data, std::string scene_name)
{
    std::string filename = "csv\\UI\\";
    filename += scene_name + ".csv";

    std::ifstream ifs(filename);
    if (!ifs) {
        return;
    }

    //csv�t�@�C����1�s���ǂݍ���
    std::string str;
    while (!ifs.eof()) {
        std::string token;
        std::istringstream stream(str);

        int i = 0;
        int temp_i[4];
        std::string temp_s;
        std::string temp_data;

        while (getline(stream, token, ',')) {
            if (token.find("#") != std::string::npos) {
                if (i < 4) {
                    temp_i[i] = stoi(token);
                }
                else if(i == 5){
                    temp_s = token;
                }
                else {
                    temp_data = token;
                }
            }
            i++;
        }

        ui_data.push_back(UIContent(temp_i[0], temp_i[1], temp_i[2], temp_i[3], temp_s,temp_data));
    }
}

void CSVDataLoader::LoadCharaCSV(std::vector<CharaBase*>& chara_data, std::string stage_name)
{
    std::string filename = stage_name + ".csv";
    std::ifstream ifs(filename);
    if (!ifs) {
        return;
    }

    //csv�t�@�C����1�s���ǂݍ���
    std::string str;
    while (!ifs.eof()) {
        std::string token;
        std::istringstream stream(str);


        while (getline(stream, token, ',')) {
            //���}���u
    //      chara_data.push_back(new CharaBase(token));
        }


    }
}
