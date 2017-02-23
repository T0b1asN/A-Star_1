#pragma once
#include "SFML.h"
#include "curr.h"

#include <vector>

#include <iostream>

class Map
{
private:
	sf::Vector2i size;
	std::vector<std::vector<int>> map;
	std::vector<sf::RectangleShape> fields;

	void priv_setup();

	sf::Vector2i startPos;
	sf::Vector2i endPos;

	friend class Pathfinder;
public:
	Map(sf::Vector2i);
	~Map();

	void setup();
	void setupFromTexture(sf::Image);
	void setupFromTextPath(std::string);
	void Draw();

	void SetTile(sf::Vector2i, int);
	void SetTile(int, int, int);

	sf::Color ColorFromInt(int);

	sf::Vector2i getStartPos() { return startPos; }
	sf::Vector2i getEndPos() { return endPos; }

	sf::Vector2i getSize() { return size; }
};

