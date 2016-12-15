#include "UIContent.h"



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
};


void UIContent::Draw()
{
    _graph_data.SetPosition(_position);
    _graph_data.Draw();
}