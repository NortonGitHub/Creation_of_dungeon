#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>

#include "Graph.h"
#include "cd_666s/Resources/ResourceManager.h"

class UIContent
{
public:
    UIContent();

    UIContent(int data_number,
        std::string data_name,
        int x, int y,
        int width, int height,
        std::string type_name,
        std::string graph_name);

    UIContent(int x, int y, int width, int height, std::string scene_name, std::string str);

    UIContent(int x, 
        int y,
        std::string type_name, 
        std::string data_name,
        std::string func_type,
        unsigned int div_num_x, 
        unsigned int div_num_y);
    
    ~UIContent();

    void Draw();

    Vector2D GetPosition() const { return _position; };

    std::string GetDataName() const { return _data_name; }
    std::string GetTypeName() const { return _type_name; }
    std::string GetGraphName() const { return _graph_name; }
    std::string GetFunctionType() const { return _func_type; }

    std::string GetStr() const {
        return _string_data;
    }
    int GetInt() const {
        return _int_data;
    }

    Vector2D GetSize() const { return _size; }
    Vector2D GetSizePos() const { return Vector2D(_position._x + _size._x, _position._y + _size._y); }

    void SetFunction(std::function<void()> func) {
        particular_function = func;
    };
    std::function<void()> GetFunction() const { return particular_function; }

private:

    std::string _data_name; //
    std::string _type_name; //
    std::string _graph_name;
    std::string _func_type;

    Vector2D _position;
    Graph _graph_data;
    std::vector<Graph*> _graph_array;

    Vector2D _size;

    std::string _string_data;
    int _int_data;

    int _div_num;       //‰æ‘œ•ªŠ„‘”
    int _div_x, _div_y; //‰æ‘œ‚Ì•ªŠ„”(X,Y)

    bool is_UI_button;

    std::string particular_function_name;
    std::function<void()> particular_function;

    std::shared_ptr<ImageResource> _image_resource;
};
