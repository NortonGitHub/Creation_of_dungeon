#include "Graph.h"


Graph::Graph()
{
}

Graph::Graph(int _graph, int _width, int _height)
	: size(Vector2D(_width, _height)),
	graph(_graph)
{
}

Graph::Graph(int _graph)
{
	graph = _graph;
}

Graph::~Graph()
{
}