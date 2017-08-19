#pragma once
//#include "cd_666s/Resources/ResourceManager.h"
//#include "cd_666s/TilebaseAI/Character.h"
//#include "Graph.h"

#include "Vector2D.h"
#include <string>
#include "cd_666s/TilebaseAI/Character.h"

class PanelContent// : public GraphicalObject
{
public:
    PanelContent();
    PanelContent(Vector2D _p, std::string name, std::string func_var);


    ~PanelContent();

    std::string _name;

    std::string _func_var;   //ä÷êîÇé¶Ç∑ÉLÅ[

    Vector2D _pos;

private:
    //Sprite panel_graph;
};

