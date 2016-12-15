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
        std::string graph_name);
   
    UIContent(int x, int y, int width, int height, std::string scene_name, std::string str);

    ~UIContent(){};

    void Draw();

    Vector2D GetPosition() const { return _position; };

    std::string GetDataName() const { return _data_name; }
    std::string GetTypeName() const { return _type_name; }
    std::string GetGraphName() const { return _graph_name; }

    std::string GetStr() const {
        return _string_data;
    }
    int GetInt() const {
        return _int_data;
    }

private:

    std::string _data_name; //ƒf[ƒ^‚Ì–¼Ì
    std::string _type_name; //UI‚Ìí—Ş
    std::string _graph_name;

    Vector2D _position;
    Graph _graph_data;
    std::vector<Graph*> _graph_array;


    std::string _string_data;
    int _int_data;
};

