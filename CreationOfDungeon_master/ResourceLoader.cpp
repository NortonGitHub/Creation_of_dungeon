#include "ResourceLoader.h"
#include <istream>


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}


std::vector<int> ResourceLoader::Load(std::string file_name, int all_num, int x_num, int y_num, int x_size, int y_size)
{
    //画像配列のハンドルのまとまり
    std::vector<int> handles(all_num, 0);

    //png形式画像のロード
    std::string format = ".png";
    LoadDivGraph((file_name + format).c_str(), all_num, x_num, y_num, x_size, y_size, handles.data());

    //関数を抜けると消滅するのでmove渡しで
    //インスタンスを渡す
    return std::move(handles);
}


int ResourceLoader::Load(std::string file_name)
{
    std::string format = ".png";
    return LoadGraph((file_name + format).c_str());
}
