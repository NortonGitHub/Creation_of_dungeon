#pragma once
#include <string>
#include<vector>
#include<stdexcept>
#include "Graph.h"
class UIContent
{
public:
    UIContent();
    UIContent(int data_number,
        std::string data_name,
        int x, int y,
        int width, int height,
        std::string type_name,
        std::string graph_name) {
        _data_number = data_number;
        _data_name = data_name;
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _type_name = type_name;
        _graph_name = graph_name;
    };

    /*
    x : x座標(左上)
    y : y座標(左上)
    width : 横幅
    height : 縦幅
    type_name : UIのタイプ(message,button,graph,or nothing)
    data_name : UIの名称, 画像ファイルもこれで決定
    div_num_x : 画像データのX軸の分割数
    div_num_y : 画像データのY軸の分割数(一枚絵の場合は両者とも1)
    */
    UIContent(int x, int y, int width, int height, std::string type_name, std::string data_name,unsigned int div_num_x , unsigned int div_num_y ) {

        const std::vector<std::string> TYPE_DATA = { "nothing" ,"message","button","graph" };

        auto it = std::find(TYPE_DATA.begin(), TYPE_DATA.end(), type_name);

        _x = x;
        _y = y;
        _width = width;
        _height = height;

        _div_x = (div_num_x > 0) ? div_num_x : 1;
        _div_y = (div_num_y > 0) ? div_num_y : 1;
        _div_num = _div_x*_div_y;

        _data_name = data_name;

        if (it != TYPE_DATA.end()) {
            _type_name = type_name;
        }
        else {
            _type_name = TYPE_DATA[0];
        }

        Graph orig_graph = Graph(data_name);

        std::vector<Graph> graph_div;

        for (size_t i = 0; i < graph_div.size(); i++) {
            _graph_array[i] = graph_div[i];
        }

        if (type_name == "button") {
            is_UI_button = true;
        }
        else {
            is_UI_button = false;
        }

    };

    ~UIContent() {
    };

    int GetDataNum() const { return _data_number; }
    int GetPosX() const { return _x; }
    int GetPosY() const { return _y; }
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    std::string GetStr() const {
        return _string_data;
    }

    int GetInt() const {
        return _int_data;
    }

    Graph GetGraph() const { return _graph_data; }
    Graph GetGraphArray(int _element) const { return _graph_array[_element]; }
    void GetGraphArray(std::vector<Graph> &graph_array) {
        for (size_t i = 0; i < _graph_array.size(); i++) {
            graph_array[i] = _graph_array[i];
        }
    }

    std::string GetDataName() const { return _data_name; }
    std::string GetTypeName() const { return _type_name; }
    std::string GetGraphName() const { return _graph_name; }

#if 0
    /*String型やint型などのデータ型を格納できる*/
    template<typename T>
    class Type {
    public:
        void Set(T value) { _value = value; }
        T Get() const { return _value; }
    private:
        T _value;
    };
#endif


private:
    int _data_number;
    std::string _data_name; //データの名称
    int _x, _y;
    int _width, _height;
    int _div_num;
    int _div_x, _div_y;
    std::string _type_name; //UIの種類
    std::string _graph_name;

    Graph  _graph_data;
    std::vector<Graph> _graph_array;

    std::string _string_data;   //メッセージ
    int _int_data;

    bool is_UI_button;

};

