#pragma once
#include "Vector2D.h"
#include <string>

class Graph
{
public:
    Graph();
    Graph(int _graph);
    Graph(int _graph,int _width,int _height);
    ~Graph();

    Vector2D GetSize()const { return size; }

    int GetGraph() const { return graph; }

private:

    Vector2D size;

    Vector2D pos;

    int graph;
};

