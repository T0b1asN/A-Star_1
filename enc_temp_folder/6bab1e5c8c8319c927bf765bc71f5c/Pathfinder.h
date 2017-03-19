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
	Map2_0& map;
	int run = 0;

	bool finished = false;
	bool noSolution = false;

	//use Positions in Map?
	std::vector<sf::Vector2i> openSet;
	std::vector<sf::Vector2i> closedSet;

	float hCost(Node a, Node b);

	Node old;

	std::vector<sf::Vector2i> path;

	std::vector<Node> openL;
	std::vector<Node> closedL;
public:
	Pathfinder(Map2_0& pMap);
	void reconstructPath(sf::Vector2i start, sf::Vector2i pEnd);

	void Solve();
	void Step();

	int Eff_Solve();

	void Draw();

	bool isFinished() { return finished; }
	bool hasSolution() { return !noSolution; }

	void finish();
};

//obsolete
std::vector<sf::Vector2i>::iterator RemoveFromOACList(std::vector<sf::Vector2i>& l, sf::Vector2i& obj);
//obsolete
std::vector<sf::Vector2i>::iterator FindInList(std::vector<sf::Vector2i>& l, sf::Vector2i& obj);

std::vector<Node>::iterator RemoveFromNodeVec(std::vector<Node>& l, Node& obj);
std::vector<Node>::iterator FindInNodeVec(std::vector<Node>& l, Node& obj);
