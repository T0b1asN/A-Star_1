#include "Node.h"

Node::Node()
{
	f = 10000.0f;
	g = 0;
	h = 10000.0f;
	parent = sf::Vector2i(-1, -1);
}

Node::Node(sf::Vector2i pPos)
{
	f = 10000.0f;
	g = 0;
	h = 10000.0f;

	pos = pPos;
	parent = sf::Vector2i(-1, -1);
}

Node::~Node()
{

}

bool Node::operator==(const Node& rhs) const
{
	if (this->pos.x == rhs.pos.x && this->pos.y == rhs.pos.y)
		return true;
	return false;
}

void Node::addNbs(Map2_0& map)
{
	int nbs = 0;
	if (pos.x > 0)
	{
		neighbours.push_back(pos - sf::Vector2i(1, 0));
		nbs++;
	}
	if (pos.x < map.getSize().x - 1)
	{
		neighbours.push_back(pos + sf::Vector2i(1, 0));
		nbs++;
	}

	if (pos.y > 0)
	{
		neighbours.push_back(pos - sf::Vector2i(0, 1));
		nbs++;
	}
	if (pos.y < map.getSize().y - 1)
	{
		neighbours.push_back(pos + sf::Vector2i(0, 1));
		nbs++;
	}

	//Diagonal
	//left, up
	if (pos.x > 0 && pos.y > 0)
	{
		neighbours.push_back(pos + sf::Vector2i(-1, -1));
	}
	//left, down
	if (pos.x > 0 && pos.y < map.getSize().y - 1)
	{
		neighbours.push_back(pos + sf::Vector2i(-1, 1));
	}
	//right, up
	if (pos.x < map.getSize().x - 1 && pos.y > 0)
	{
		neighbours.push_back(pos + sf::Vector2i(1, -1));
	}
	//right, down
	if (pos.x < map.getSize().x && pos.y < map.getSize().y - 1)
	{
		neighbours.push_back(pos + sf::Vector2i(1, 1));
	}
}

void Node::Draw()
{
	sf::CircleShape point(cr::getFieldW() / 2.0f - 1.0f);
	point.setPosition(sf::Vector2f(pos * cr::getFieldW()) + sf::Vector2f(0.5f, 0.5f));
	point.setFillColor(debCol);
	cr::currWin().draw(point);
}
std::ostream& operator<<(std::ostream& os, sf::Color c)
{
	os << "{" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "}";
	return os;
}

void Node::setNode(Node& other)
{
	f = other.getF();
	g = other.getG();
	h = other.getH();;

	neighbours = other.getNbs();

	pos = other.getPos();
	parent = other.getParent();
}

bool Node::operator<(Node& rhs) const
{
	return (this->f < rhs.f);
}

bool Node::operator==(Node& rhs) const
{
	return (this->f == rhs.f && this->g == rhs.g && this->h == rhs.h &&
		this->pos.x == rhs.pos.x && this->pos.y == rhs.pos.y && this->obstacle == rhs.obstacle);
}
