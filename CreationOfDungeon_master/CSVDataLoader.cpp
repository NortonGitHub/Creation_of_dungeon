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

    //csvファイルを1行ずつ読み込む
    std::string str;
    int now_row = 0;    //行
    int now_column = 0; //列    

    while (!ifs.eof()) {
        std::string token;
        std::istringstream stream(str);

        now_column = 0;

        while (getline(stream, token, ',')) {
            //すべて文字列として読み込まれるため
            //数値は変換が必要

            int temp = stoi(token); //stof(string str) : stringをfloatに変換
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
data_name : UIの名称, 画像ファイルもこれで決定
div_num_x : 画像データのX軸の分割数
div_num_y : 画像データのY軸の分割数(一枚絵の場合は両者とも1)
*/
void CSVDataLoader::LoadUICSV(std::vector<UIContent> &ui_data, std::string scene_name)
{
    std::string filename = "csv\\UI\\" + scene_name + ".csv";

    std::ifstream ifs(filename);
    if (!ifs) {
        return;
    }

    //csvファイルを1行ずつ読み込む
    std::string str;
    while (getline(ifs, str)) {
        std::string token;
        std::istringstream stream(str);

        int i = 0;
        int temp_i[4] = { -1,-1,-1,-1 };
        int temp_div[2] = { 1,1 };
        std::string temp_s = "";
        std::string temp_data_name = "";

        std::vector<std::string> temp;
        temp.reserve(9);

        while (getline(stream, token, ',')) {
            auto n = token.find("#");
            auto m = token.find("\n");
            if (n == std::string::npos && m == std::string::npos) {
                /*
                if (i < 4) {
                    temp_i[i] = stoi(token);
                }
                else if (i == 4) {
                    temp_s = token;
                }
                else if (i == 5) {
                    temp_data_name = token;
                }
                else {
                    temp_div[i - 6] = stoi(token);
                }
                */

                temp.push_back(token);
                i++;
            }
        }

        if(temp.size() <= 0){
            continue;
        }

        for (int i = 0; i < temp.size();i++) {
            auto b = temp[i];
        }

        if (temp[4] != "" && temp[5] != ""/*temp_s != "" && temp_data_name != ""*/) {
            //          ui_data.push_back(UIContent(temp_i[0], temp_i[1], temp_i[2], temp_i[3], temp_s, temp_data_name, temp_div[0], temp_div[1]));
            ui_data.push_back(UIContent(stoi(temp[0]), stoi(temp[1]), temp[2], temp[3], stoi(temp[4]), stoi(temp[5])));
        }

        temp.clear();
        temp.resize(0);
    }

}

void CSVDataLoader::LoadCharaCSV(std::vector<CharaBase*>& chara_data, std::string stage_name)
{
    std::string filename = stage_name + ".csv";
    std::ifstream ifs(filename);
    if (!ifs) {
        return;
    }

    //csvファイルを1行ずつ読み込む
    std::string str;
    while (!ifs.eof()) {
        std::string token;
        std::istringstream stream(str);


        while (getline(stream, token, ',')) {
            //応急処置
    //      chara_data.push_back(new CharaBase(token));
        }


    }
}
