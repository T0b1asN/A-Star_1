#pragma once
#include "SFML.h"

#include <vector>
#include "Map2_0.h"

#include <iostream>

class Map2_0;

std::ostream& operator<<(std::ostream& os, sf::Color c);


class Node
{
private:
	float g, h, f;

	sf::Vector2i pos;
	std::vector<Node> neighbours;
public:
	Node();
	Node(sf::Vector2i pPos);
	~Node();

	sf::Vector2i getPos() { return pos; }

	float getF() { return f; }
	float getG() { return g; }
	float getH() { return h; }

	void setF(float pF) { f = pF; }
	void setG(float pG) { g = pG; }
	void setH(float pH) { h = pH; }

	bool Node::operator==(const Node& rhs) const;

	void addNbs(Map2_0& map);

	std::vector<Node> getNbs() { std::cout << "HI " << neighbours.size() << std::endl; return neighbours; }

	void Draw();

	sf::Color debCol = sf::Color::White;
};

