#include "Pathfinder.h"

Pathfinder::Pathfinder(Map2_0& pMap):
	map(pMap)
{
	
}

int Pathfinder::Eff_Solve()
{
	int run = 0;
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
		//record node
		Node rec;
		
		//get new best Tile in openL, put it in rec
		for (Node& n : openL)
		{
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
		
		//Color evaluated tiles blue
		if (rec.getPos() != map.getStart())
			map.nodes.at(rec.getPos().x).at(rec.getPos().y).debCol = sf::Color::Blue;

		//Remove rec from openL
		openL.erase(std::remove(openL.begin(), openL.end(), rec));
		//Put rec in closedL
		closedL.push_back(rec);

		if (rec.getPos() == map.getEnd())
		{
			//std::cout << closedL.size() << std::endl;
			return 1;//Finish
		}

		//Add possible neighbours to the open list
		for (Node& nb : rec.getNbs())
		{
			//continue to next neighbour, if it is in the closedL, if it is an obstacle, or if it is the start
			if (std::find(closedL.begin(), closedL.end(), nb) != closedL.end() || 
				map.nodes.at(nb.getPos().x).at(nb.getPos().y).isObstacle() ||
				nb.getPos() == map.getStart())
				continue;

			//check if the neighbours complete cost is more than the possible new cost
			//or if it is not in the open list
			if ((nb.getF() > (rec.getG() + 1 + hCost(rec, map.getEnd()))) || (std::find(openL.begin(), openL.end(), nb) == openL.end()))
			{
				//set the new complete(F) cost and parent
				nb.setF(rec.getG() + 1 + hCost(rec, map.getEnd()));
				nb.setParent(rec.getPos());

				//check if neighbour is not in the open list
				if (std::find(openL.begin(), openL.end(), nb) == openL.end())
				{
					//Error handling
					try
					{
						//put neighbour in open list and set changes in the node map
						openL.push_back(nb);
						map.nodes.at(nb.getPos().x).at(nb.getPos().y).setNode2(nb);
					}
					catch (const std::out_of_range& oor) {
						//catch out of range errors in vectors
						std::cerr << "Out of Range error: " << oor.what() << " at run: " << run << std::endl;
						std::cout << "NB-Pos: " << nb.getPos().x << " | " << nb.getPos().y << std::endl;
						std::cout << "OpenL-Count: " << openL.size() << std::endl;
						std::system("PAUSE");
					}
					run++;
				}
			}
		}
	}
	return 0;
}

//get the heuristic cost between 2 tiles
float Pathfinder::hCost(Node a, Node b)
{
	//heuristic cost
	if (cr::getDiag())
	{
		//diagonal distance
		float dx = (float)std::abs(a.getPos().x - b.getPos().x);
		float dy = (float)std::abs(a.getPos().y - b.getPos().y);
		return 1.f * (dx + dy) + (1.f - 2 * 1.f) * std::min(dx, dy);
	}
	else
	{
		//Manhattan square cost
		float dx = (float)std::abs(a.getPos().x - b.getPos().x);
		float dy = (float)std::abs(a.getPos().y - b.getPos().y);
		return 1.f * (dx + dy);
	}
}

//reconstruct the path, saved in local variable
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
