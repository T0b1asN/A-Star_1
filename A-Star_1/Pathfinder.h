#pragma once
#include "SFML.h"
#include "curr.h"
#include "Map2_0.h"
#include "Node.h"

#include <iostream>
#include <vector>


class Pathfinder
{
private:
	Map2_0 map;

	bool finished;
	bool noSolution = true;

	//use Positions in Map?
	std::vector<Node> openSet;
	std::vector<Node> closedSet;

	float hCost(Node a, Node b);
public:
	Pathfinder(Map2_0& pMap);

	void Solve();
	void Step();

	void Draw();
};
