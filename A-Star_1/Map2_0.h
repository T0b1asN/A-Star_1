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
	//the "real" map
	std::vector<std::vector<Node>> nodes;

	//size of the map
	sf::Vector2i size;

	//start and end coordinates
	sf::Vector2i start, end;

	//the path over the map
	std::vector<sf::Vector2i> path;
public:
	Map2_0();
	Map2_0(std::string textPath);
	Map2_0(sf::Image img);
	~Map2_0();

	sf::Vector2i getStart() { return start; }
	sf::Vector2i getEnd() { return end; }

	sf::Vector2i getSize() { return size; }

	void Draw();

	void PrintSize();

	friend class Pathfinder;

	//basically a constructor, but you can call it later in the process
	//it remakes the map
	void setupFromImage(sf::Image img);

	void setPath(std::vector<sf::Vector2i> _path) { path = _path; }
	std::vector<sf::Vector2i> getPath() { return path; }
};

