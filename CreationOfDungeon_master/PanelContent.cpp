#include "PanelContent.h"



PanelContent::PanelContent()
{
}

PanelContent::PanelContent(Vector2D _p, std::string name, std::string func_var)
    : _position(_p), _name(name), _func_var(func_var)
{
    std::string filename = "graph/ui/" + _name + ".png";

    _graph.Load(filename);

    _graph.SetPosition(_position);
    _graph.SetPriority(Sprite::Priority::UI);
    //_graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

}


PanelContent::~PanelContent()
{
}
