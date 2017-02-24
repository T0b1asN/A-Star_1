#pragma once
#include "SFML.h"
#include "curr.h"

#include "Node.h"

#include <vector>

#include <iostream>

class Node;

class Map2_0
{
private:
	std::vector<std::vector<Node>> nodes;

	sf::Vector2i size;

	sf::Vector2i start, end;
public:
	Map2_0();
	Map2_0(std::string textPath);
	Map2_0(sf::Image img);
	~Map2_0();

	sf::Vector2i getStart() { return start; }
	sf::Vector2i getEnd() { return end; }

	sf::Vector2i getSize() { return size; }

	void Draw();

	friend class Pathfinder;
};

