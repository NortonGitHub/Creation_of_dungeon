#include "UIContent.h"
#include"DxLib.h"
#include "ResourceLoader.h"
#include <assert.h>

UIContent::UIContent()
{
}


UIContent::UIContent(int data_number,
    std::string data_name,
    int x, int y,
    int width, int height,
    std::string type_name,
    std::string graph_name)
{
    _data_name = data_name;

    _type_name = type_name;
    _graph_name = graph_name;
}


UIContent::UIContent(int x, int y, int width, int height, std::string scene_name, std::string str)
    : _position(Vector2D(x, y))
{
    _type_name = scene_name;

    try {
        _int_data = std::stoi(str, nullptr, 10);
    }
    catch (const std::invalid_argument& e) {
        _string_data = str;
    }
}

UIContent::UIContent(int x, int y, std::string type_name, std::string data_name, std::string func_type, unsigned int div_num_x, unsigned int div_num_y) {

    const std::vector<std::string> TYPE_DATA = { "nothing" ,"message","button","graph" };

    auto it = std::find(TYPE_DATA.begin(), TYPE_DATA.end(), type_name);

    _position.Set(x, y);

    _div_x = (div_num_x > 0) ? div_num_x : 1;
    _div_y = (div_num_y > 0) ? div_num_y : 1;
    _div_num = _div_x*_div_y;

    _data_name = data_name;

    _type_name = (it != TYPE_DATA.end()) ? type_name : TYPE_DATA[0];

    //    _graph_data = Graph(data_name);
    //    _graph_data.Load(data_name);

    is_UI_button = (type_name == "button") ? true : false;

    particular_function_name = data_name;

    _func_type = func_type;

    //ébíË
    std::string load_name = "resourse/" + data_name;
    _test_handle = std::move(ResourceLoader::Load(load_name.c_str()));
    //assert((_test_handle != -1) && "âÊëúì«Ç›çûÇ›é∏îs");
    int _sizeX, _sizeY;
    GetGraphSize(_test_handle, &_sizeX, &_sizeY);
    _size.Set(_sizeX, _sizeY);
}

UIContent::~UIContent()
{
//    DeleteGraph(_test_handle);
}


void UIContent::Draw()
{
    //_graph_data.SetPosition(_position);
    //_graph_data.Draw();

    //ébíË
    DrawGraph(_position._x, _position._y, _test_handle, FALSE);
}