#pragma once
#include <vector>
#include "HeroBase.h"
#include "Graph.h"

class SwordHero :
	public HeroBase
{
public:
	SwordHero();
	~SwordHero();

	void Update();
	void Draw();


private:
	Vector2D body;
	std::vector<Graph> graph;
};

