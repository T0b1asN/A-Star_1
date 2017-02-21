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
public:
	Map(sf::Vector2i);
	~Map();

	void setup();
	void setupFromTexture(sf::Image);
	void setupFromTextPath(std::string);
	void Draw();
};

