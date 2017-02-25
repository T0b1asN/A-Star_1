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
						//else
						//	continue;
						//continue;
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

void Pathfinder::Eff_Solve()
{
	Node* startN = new Node(map.getStart());

	startN->setObstacle(false);
	startN->setG(0.f);
	startN->setH(hCost(*startN, map.getEnd()));
	startN->setF(startN->getH() + startN->getG());
	startN->addNbs(map);

	openL.push_back(*startN);
	delete startN;


	while (openL.size() > 0)
	{
		std::cout << "Open Size: " << openL.size() << std::endl;
		Node rec;
		std::cout << "Rec F score: " << rec.getF() << std::endl;
		for (Node& n : openL)
		{
			std::cout << "n F score: " << n.getF() << std::endl;
			std::cout << "n\'s neighbours: " << n.getNbs().size() << std::endl;
			if (n < rec)
			{
				rec.setNode(n);
			}
			else if (n.getF() == rec.getF())
				if (n.getH() < rec.getH())
					rec.setNode(n);
		}

		std::cout << "rec F score: " << rec.getF() << std::endl;
		std::cout << "rec\'s neighbours: " << rec.getNbs().size() << std::endl;

		std::cout << (FindInNodeVec(openL, rec) == openL.end()) << std::endl;

		//if (RemoveFromNodeVec(openL, rec) == openL.end())
		//	std::system("PAUSE");
		openL.erase(std::remove(openL.begin(), openL.end(), rec));

		closedL.push_back(rec);

		if (rec.getPos() != map.getStart() && rec.getPos() != map.getEnd())
			map.nodes.at(rec.getPos().x).at(rec.getPos().y).debCol = sf::Color::Blue;
		else if (rec.getPos() == map.getStart())
			map.nodes.at(rec.getPos().x).at(rec.getPos().y).debCol = sf::Color::Green;
		else if (rec.getPos() == map.getEnd())
			map.nodes.at(rec.getPos().x).at(rec.getPos().y).debCol = sf::Color::Red;

		if (rec.getPos() == map.getEnd())
			return;//Finish

		std::cout << "Evaluating neighbours: " << rec.getNbs().size() << std::endl;
		for (Node nb : rec.getNbs())
		{
			if (std::find(openL.begin(), openL.end(), nb) != openL.end())
				continue;

			if ((nb.getF() > (rec.getG() + 1 + hCost(rec, map.getEnd()))) || (std::find(openL.begin(), openL.end(), nb) == openL.end()))
			{
				nb.setF(rec.getG() + 1 + hCost(rec, map.getEnd()));
				nb.setParent(rec.getPos());

				if (std::find(openL.begin(), openL.end(), nb) == openL.end())
				{
					openL.push_back(nb);
					openL.back().addNbs(map);
				}

				std::cout << "Free Neighbour" << std::endl;
			}
		}
		_sleep(100);
	}
}

float Pathfinder::hCost(Node a, Node b)
{
	return (float)sqrt(pow(a.getPos().x - b.getPos().x, 2) + pow(a.getPos().y - b.getPos().y, 2));

	//Option
	//h = min(dx, dy) * 14 + abs(dx - dy) * 10
	//val dx = abs(goalXcoord - nodeXcoordinate)
	//val dy = abs(goalYcoord - nodeYcoordinate)
	//min smaller of two values
	//abs absolute value
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
	path.push_back(sf::Vector2i(1, 1));
	//Node& end = map.nodes.at(pEnd.x).at(pEnd.y);

	//Node curr = end;
	//while (curr.getParent() != map.getStart())
	//{
	//	path.push_back(curr.getPos());
	//	curr = map.nodes.at(curr.getParent().x).at(curr.getParent().y);
	//}
	//path.push_back(curr.getPos());
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

std::vector<Node>::iterator RemoveFromNodeVec(std::vector<Node>& l, Node& obj)
{
	std::vector<Node>::iterator it = l.begin();

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

std::vector<Node>::iterator FindInNodeVec(std::vector<Node>& l, Node& obj)
{
	std::vector<Node>::iterator it = l.begin();

	for (; it != l.end(); ++it)
	{
		if (*it == obj)
			break;
	}
	return it;
}
