#include "Pathfinder.h"

Pathfinder::Pathfinder(Map2_0& pMap):
	map(pMap)
{
	openSet.push_back(map.getStart());
	openSet.at(0).addNbs(map);
}

void Pathfinder::Solve()
{
	while (!finished && !noSolution)
	{
		Step();
	}
}

void Pathfinder::Step()
{
	//std::cout << (int)openSet.size() << std::endl;
	if (openSet.size() > 0)
	{
		for (Node n : closedSet)
		{
			map.nodes.at(n.getPos().x).at(n.getPos().y).debCol = sf::Color::Black;
			std::cout << "Col1: " << map.nodes.at(n.getPos().x).at(n.getPos().y).debCol << std::endl;
		}

		int winner = 0;
		for (int i = 0; i < openSet.size(); i++)
		{
			if (openSet.at(i).getF() < openSet.at(winner).getF())
			{
				winner = i;
			}
		}

		if (openSet.at(winner).getPos() == map.getEnd())
		{
			finished = true;
		}

		Node curr = openSet.at(winner);
		openSet.erase(std::remove(openSet.begin(), openSet.end(), openSet.at(winner)));
		closedSet.push_back(curr);

		std::cout << curr.getNbs().size() << std::endl;

		//eventuell Fehler:
		//	nB ist keine Referenz, also wird der neue Wert nicht in den Vector uebertragen
		for (Node nb : curr.getNbs())
		{
			if (std::find(closedSet.begin(), closedSet.end(), nb) == closedSet.end())
			{
				int tempG = curr.getG() + 1;

				if (std::find(openSet.begin(), openSet.end(), nb) != openSet.end())
				{
					if (tempG < nb.getG())
					{
						nb.setG(tempG);
					}
				}
				else
				{
					nb.setG(tempG);
					openSet.push_back(nb);
				}

				nb.setH(hCost(nb, map.getEnd()));
				nb.setF(nb.getG() + nb.getH());
			}
			std::cout << "Neigbour" << std::endl;
		}
	}
	else
		noSolution = true;
}

float Pathfinder::hCost(Node a, Node b)
{
	return sqrt(pow(a.getPos().x - b.getPos().x, 2) + pow(a.getPos().y - b.getPos().y, 2));
}


