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
	//the costs of the Node
	float g, h, f;

	//Position of the node
	sf::Vector2i pos;
	//neighbours of the Node
	std::vector<Node> neighbours;

	//is the Node an obstacle
	bool obstacle = false;

	//the node's parent
	sf::Vector2i parent;
public:
	Node();
	Node(sf::Vector2i pPos);
	~Node();

	sf::Vector2i getPos() { return pos; }

	//getter and setter for the costs
	float getF() { return f; }
	float getG() { return g; }
	float getH() { return h; }

	void setF(float pF) { f = pF; }
	void setG(float pG) { g = pG; }
	void setH(float pH) { h = pH; }

	//adds the neighbours on a map
	void addNbs(Map2_0& map);

	bool Node::operator==(const Node& rhs) const;

	std::vector<Node> getNbs() { return neighbours; }

	//set this node to another
	void setNode(Node& other);
	//same as setNode() but without the neighbours
	void setNode2(Node& other);

	//draw the Node on the current window
	void Draw();

	//Color of the Node
	sf::Color debCol = sf::Color::White;

	//getters and setters for the obstacle state and the parent
	void setObstacle(bool state) { obstacle = state; }
	bool isObstacle() { return obstacle; }

	sf::Vector2i getParent() { return parent; }
	void setParent(sf::Vector2i pPar) { parent = pPar; }

//operators
public:
	bool operator<(Node& rhs) const;
	bool operator==(Node& rhs) const;
};
