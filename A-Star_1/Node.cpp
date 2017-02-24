#include "Node.h"

Node::Node()
{

}

Node::Node(sf::Vector2i pPos)
{
	pos = pPos;
}

Node::~Node()
{

}

bool Node::operator==(const Node& rhs) const
{
	if (this->pos == rhs.pos)
		return true;
	return false;
}

void Node::addNbs(Map2_0& map)
{
	std::cout << "added NBs" << std::endl;
	if (pos.x > 0)
		neighbours.push_back(pos - sf::Vector2i(1, 0));
	if (pos.x < map.getSize().x - 1)
		neighbours.push_back(pos + sf::Vector2i(1, 0));

	if (pos.x > 0)
		neighbours.push_back(pos - sf::Vector2i(0, 1));
	if (pos.x < map.getSize().y - 1)
		neighbours.push_back(pos + sf::Vector2i(0, 1));
}

void Node::Draw()
{
	sf::CircleShape point(5.0f);
	point.setPosition(sf::Vector2f(pos * cr::getFieldW()));
	cr::currWin().draw(point);
}
std::ostream& operator<<(std::ostream& os, sf::Color c)
{
	os << "{" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "}";
	return os;
}
