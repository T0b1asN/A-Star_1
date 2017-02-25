#include "Pathfinder.h"

Pathfinder::Pathfinder(Map2_0& pMap):
	map(pMap)
{
	openSet.push_back(map.getStart());
	//map.nodes.at(openSet.at(0).x).at(openSet.at(0).y).addNbs(map);
}

void Pathfinder::Solve()
{
	while (!finished && !noSolution)
	{
		Step();
	}
	if (noSolution)
	{
		std::cout << "No Solution!" << std::endl;
		return;
	}
	else
	{
		reconstructPath(map.getStart(), map.getEnd());
		std::cout << "Finished after " << run << " runs!" << std::endl;
		std::cout << "Pathlength: " << path.size() << std::endl;
		for (sf::Vector2i v : path)
		{
			map.nodes.at(v.x).at(v.y).debCol = sf::Color::Yellow;
		}

		map.nodes.at(map.getStart().x).at(map.getStart().y).debCol = sf::Color::Green;
		map.nodes.at(map.getEnd().x).at(map.getEnd().y).debCol = sf::Color::Red;
	}
}

void Pathfinder::Step()
{
	//std::cout << (int)closedSet.size() << std::endl;
	if (openSet.size() > 0)
	{
		run++;
		//std::cout << std::endl << "Run: " << run << std::endl;
		int winner = 0;
		for (int i = 0; (unsigned int)i < openSet.size(); i++)
		{
			sf::Vector2i opPos = openSet.at(i);
			sf::Vector2i winPos = openSet.at(winner);
			if (map.nodes.at(opPos.x).at(opPos.y).getF() < map.nodes.at(winPos.x).at(winPos.y).getF())
			{
				winner = i;
			}
			if (opPos == map.getEnd())
			{
				winner = i;
				break;
			}
		}

		if (openSet.at(winner) == map.getEnd())
		{
			finished = true;
		}

		Node& curr = map.nodes.at(openSet.at(winner).x).at(openSet.at(winner).y);
		RemoveFromOACList(openSet, openSet.at(winner));
		closedSet.push_back(curr.getPos());

		//Coloring
		if (curr.getPos() != map.getStart() && curr.getPos() != map.getEnd())
			map.nodes.at(curr.getPos().x).at(curr.getPos().y).debCol = sf::Color::Blue;
		else if (curr.getPos() == map.getStart())
			map.nodes.at(curr.getPos().x).at(curr.getPos().y).debCol = sf::Color::Green;
		else if (curr.getPos() == map.getEnd())
			map.nodes.at(curr.getPos().x).at(curr.getPos().y).debCol = sf::Color::Red;

		//eventuell Fehler:
		//	nB ist keine Referenz, also wird der neue Wert nicht in den Vector uebertragen
		for (Node nb : curr.getNbs())
		{
			if (!map.nodes.at(nb.getPos().x).at(nb.getPos().y).isObstacle())
			{
				if (FindInList(closedSet, nb.getPos()) == closedSet.end())
				{
					int tempG = (int)curr.getG() + 1;
					
					if (FindInList(openSet, nb.getPos()) != openSet.end())
					{
						if (tempG < nb.getG())
						{
							nb.setG((float)tempG);
							//std::cout << nb.getParent().x << "|" << nb.getParent().y << std::endl;
							nb.setParent(curr.getPos());
						}
						continue;
					}
					else
					{
						nb.setG((float)tempG);
						openSet.push_back(nb.getPos());
						nb.setParent(curr.getPos());
					}

					nb.setH(hCost(nb, map.getEnd()));
					nb.getH();
					nb.setF(nb.getG() + nb.getH());
					if (nb.getParent() == sf::Vector2i(-1, -1))
						std::cout << "No Parent at " << "{" << nb.getPos().x << "|" << nb.getPos().y << "}" << std::endl;
					map.nodes.at(nb.getPos().x).at(nb.getPos().y).setNode(nb);
				}
			}
			//std::cout << "Neigbour" << std::endl;
		}
		old = curr;
	}
	else
		noSolution = true;
}

float Pathfinder::hCost(Node a, Node b)
{
	return (float)sqrt(pow(a.getPos().x - b.getPos().x, 2) + pow(a.getPos().y - b.getPos().y, 2));
}

std::vector<sf::Vector2i>::iterator RemoveFromOACList(std::vector<sf::Vector2i>& l, sf::Vector2i& obj)
{
	std::vector<sf::Vector2i>::iterator it = l.begin();

	for (; it != l.end(); ++it)
	{
		if (*it == obj)
		{
			l.erase(it);
			break;
		}
	}
	return it;
}

std::vector<sf::Vector2i>::iterator FindInList(std::vector<sf::Vector2i>& l, sf::Vector2i& obj)
{
	std::vector<sf::Vector2i>::iterator it = l.begin();

	for (; it != l.end(); ++it)
	{
		if (*it == obj)
			break;
	}
	return it;
}

void Pathfinder::reconstructPath(sf::Vector2i start, sf::Vector2i pEnd)
{
	Node& end = map.nodes.at(pEnd.x).at(pEnd.y);

	Node curr = end;
	while (curr.getParent() != map.getStart())
	{
		path.push_back(curr.getPos());
		curr = map.nodes.at(curr.getParent().x).at(curr.getParent().y);
	}
	path.push_back(curr.getPos());
}

void Pathfinder::finish()
{
	reconstructPath(map.getStart(), map.getEnd());
	std::cout << "Finished after " << run << " runs!" << std::endl;
	std::cout << "Pathlength: " << path.size() << std::endl;
	for (sf::Vector2i v : path)
	{
		map.nodes.at(v.x).at(v.y).debCol = sf::Color::Yellow;
	}

	map.nodes.at(map.getStart().x).at(map.getStart().y).debCol = sf::Color::Green;
	map.nodes.at(map.getEnd().x).at(map.getEnd().y).debCol = sf::Color::Red;
}
