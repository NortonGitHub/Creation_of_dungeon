#include "PanelContent.h"



PanelContent::PanelContent()
{
}

PanelContent::PanelContent(Vector2D _p, std::string name, std::string func_var)
    : _pos(_p), _name(name), _func_var(func_var)
{
    //std::string filename = "graph/ui/" + name + ".png";
        //_name + ".png";
    //_position.Set(_p._x,_p._y);


    //_graph = Sprite(filename);
    //_graph.Load(filename);

    /*緊急処置でDXライブラリ単体の処理に*/


    //_graph = std::move(Sprite(filename, _position));

    //auto test = _graph.GetResourceHandle();

   // _graph.SetPosition(_position);
    //_graph.SetPriority(Sprite::Priority::UI);
    //_graph.SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));

}

PanelContent::~PanelContent()
{
}
