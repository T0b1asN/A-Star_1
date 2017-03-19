#include "Pathfinder.h"

Pathfinder::Pathfinder(Map2_0& pMap):
	map(pMap)
{
	openSet.push_back(map.getStart());
}

int Pathfinder::Eff_Solve()
{
	//map.nodes.at(0).at(0).debCol;
	//std::system("PAUSE");
	int run = 0;
	//Start Node Setup
	Node* startN = new Node(map.getStart());

	startN->setObstacle(false);
	startN->setG(0.f);
	startN->setH(hCost(*startN, map.getEnd()));
	startN->setF(startN->getH() + startN->getG());
	startN->addNbs(map);

	openL.push_back(*startN);
	delete startN;

	//main loop
	while (openL.size() > 0)
	{
		//Debug
		//std::cout << "Open Size: " << openL.size() << std::endl;
		//record node
		Node rec;
		//std::cout << "Rec F score: " << rec.getF() << std::endl;

		//get new best Tile in openL, put it in rec
		for (Node& n : openL)
		{
			//Debug
			//std::cout << "n F score: " << n.getF() << std::endl;
			//std::cout << "n\'s neighbours: " << n.getNbs().size() << std::endl;
			if (n < rec)
			{
				rec.setNode(n);
				rec.addNbs(map);
			}
			else if (n.getF() == rec.getF())
				if (n.getH() < rec.getH())
				{
					rec.setNode(n);
					rec.addNbs(map);
				}
		}

		//Debug
		//std::cout << "rec F score: " << rec.getF() << std::endl;
		//std::cout << "rec\'s neighbours: " << rec.getNbs().size() << std::endl;

		if (rec.getPos() != map.getStart())
			map.nodes.at(rec.getPos().x).at(rec.getPos().y).debCol = sf::Color::Blue;

		//Remove rec from openL
		openL.erase(std::remove(openL.begin(), openL.end(), rec));
		//Put rec in closedL
		closedL.push_back(rec);

		if (rec.getPos() == map.getEnd())
		{
			std::cout << closedL.size() << std::endl;
			return 1;//Finish
		}

		for (Node& nb : rec.getNbs())
		{
			if (std::find(closedL.begin(), closedL.end(), nb) != closedL.end() || 
				map.nodes.at(nb.getPos().x).at(nb.getPos().y).isObstacle() ||
				nb.getPos() == map.getStart())
				continue;

			if ((nb.getF() > (rec.getG() + 1 + hCost(rec, map.getEnd()))) || (std::find(openL.begin(), openL.end(), nb) == openL.end()))
			{
				nb.setF(rec.getG() + 1 + hCost(rec, map.getEnd()));
				nb.setParent(rec.getPos());

				if (std::find(openL.begin(), openL.end(), nb) == openL.end())
				{
					try
					{
						openL.push_back(nb);
						map.nodes.at(nb.getPos().x).at(nb.getPos().y).setNode2(nb);
					}
					catch (const std::out_of_range& oor) {
						std::cerr << "Out of Range error: " << oor.what() << " at run: " << run << std::endl;
						std::cout << "NB-Pos: " << nb.getPos().x << " | " << nb.getPos().y << std::endl;
						std::cout << "OpenL-Count: " << openL.size() << std::endl;
						std::system("PAUSE");
					}
					run++;
				}
			}
		}
		//_sleep(100);
	}
	return 0;
}

float Pathfinder::hCost(Node a, Node b)
{
	//return (float)sqrt(pow(a.getPos().x - b.getPos().x, 2) + pow(a.getPos().y - b.getPos().y, 2));

	//return std::min(a.getPos().x - b.getPos().x, a.getPos().y - b.getPos().y) * 1.4f + 
	//	std::abs((a.getPos().x - b.getPos().x) - (a.getPos().y - b.getPos().y));
	if (DIAGONAL)
	{
		float dx = abs(a.getPos().x - b.getPos().x);
		float dy = abs(a.getPos().y - b.getPos().y);
		return 1.f * (dx + dy) + (1.f - 2 * 1.f) * std::min(dx, dy);
	}
	else
	{
		float dx = abs(a.getPos().x - b.getPos().x);
		float dy = abs(a.getPos().y - b.getPos().y);
		return 1.f * (dx + dy);
	}
	//Option
	//h = min(dx, dy) * 14 + abs(dx - dy) * 10
	//val dx = abs(goalXcoord - nodeXcoordinate)
	//val dy = abs(goalYcoord - nodeYcoordinate)
	//min smaller of two values
	//abs absolute value
}

void Pathfinder::reconstructPath(sf::Vector2i start, sf::Vector2i pEnd)
{
	Node& end = map.nodes.at(pEnd.x).at(pEnd.y);

	Node curr = end;
	while (curr.getParent() != map.getStart() && curr.getParent().x > -1 && curr.getParent().y > -1)
	{
		path.push_back(curr.getPos());
		if (&curr != nullptr)
			curr = map.nodes.at(curr.getParent().x).at(curr.getParent().y);
		else
			std::cout << "nullptr" << std::endl;
	}
	path.push_back(curr.getPos());
	path.push_back(map.getStart());

	for (sf::Vector2i v : path)
	{
		map.nodes.at(v.x).at(v.y).debCol = sf::Color::Yellow;
	}

	map.nodes.at(map.getStart().x).at(map.getStart().y).debCol = sf::Color::Green;
	map.nodes.at(map.getEnd().x).at(map.getEnd().y).debCol = sf::Color::Red;

	_path = path;
	std::cout << "Pathlength: " << path.size() << std::endl;
}
