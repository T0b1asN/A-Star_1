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

	bool obstacle = false;

	sf::Vector2i parent;
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

	std::vector<Node> getNbs() { return neighbours; }

	void setNode(Node& other);

	void Draw();

	sf::Color debCol = sf::Color::White;

	void setObstacle(bool state) { obstacle = state; }
	bool isObstacle() { return obstacle; }

	sf::Vector2i getParent() { return parent; }
	void setParent(sf::Vector2i pPar) { parent = pPar; }

//operators
public:
	bool operator<(Node& rhs) const;
	bool operator==(Node& rhs) const;
};
