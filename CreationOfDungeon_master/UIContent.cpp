#include "UIContent.h"
#include"DxLib.h"
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

    is_UI_button = (type_name == "button") ? true : false;

    particular_function_name = data_name;

    _func_type = func_type;

    //Žb’è
    std::string load_name = "resource/" + data_name + ".png";
    _image_resource = IMAGE_RESOURCE_TABLE->Create(load_name);
    //assert((_test_handle != -1) && "‰æ‘œ“Ç‚Ýž‚ÝŽ¸”s");
    _size.Set(_image_resource->GetWidth(), _image_resource->GetHeight());
}

UIContent::~UIContent()
{
    _image_resource = nullptr;
}


void UIContent::Draw()
{
    //Žb’è
    //DrawGraph(_position._x, _position._y, _image_resource->GetHandle(), FALSE);
    DrawGraph(_position._x, _position._y, _image_resource->GetHandle(), TRUE);
}