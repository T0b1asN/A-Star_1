#include "Pathfinder.h"

Pathfinder::Pathfinder(Map& pMap) :
	map(pMap)
{
	startPos = map.getStartPos();
	endPos = map.getEndPos();
	currPos.pos = startPos;
	currPos.GCost = 0;
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::Setup()
{
	//Now do the first Step
	//doesnt work now, add walkable tiles first

	for (int x = startPos.x - 1; x <= startPos.x + 1; x++)
	{
		for (int y = startPos.y - 1; y <= startPos.y + 1; y++)
		{
			if (sf::Vector2i(x, y) != startPos)
			{
				Tile _some(sf::Vector2i(x, y), 1, 1 + GetHCost(Tile(sf::Vector2i(x, y))));
				openList.push_back(_some);
			}
		}
	}
}

void Pathfinder::Step()
{
	if (!foundPath)
	{
		Tile newT;
		for (const Tile t : openList)
		{
			if (t.cost <= newT.cost && !TileVectorContains(closedList, t))
			{
				newT = t;
				DeleteTileFromVector(openList, newT);
			}
		}

		if (newT.pos == endPos)
		{
			foundPath = true;
		}

		closedList.push_back(newT);

		for (int x = newT.pos.x - 1; x <= newT.pos.x + 1; x++)
		{
			for (int y = newT.pos.y - 1; y <= newT.pos.y + 1; y++)
			{
				if (inMap(sf::Vector2i(x, y)))
				{
					if (sf::Vector2i(x, y) != newT.pos && map.map.at(x).at(y) != 1 && map.map.at(x).at(y) != 4)
					{
						//Tile _some(sf::Vector2i(x, y), newT.GCost + 1, newT.GCost + 1 + GetHCost(Tile(sf::Vector2i(x, y))));
						if (TileVectorContains(closedList, Tile(sf::Vector2i(x, y), newT.GCost + 1, newT.GCost + 1 + GetHCost(Tile(sf::Vector2i(x, y))))))
							break;
						else if (!TileVectorContains(openList, Tile(sf::Vector2i(x, y), newT.GCost + 1, newT.GCost + 1 + GetHCost(Tile(sf::Vector2i(x, y)))))
							&&
							!TileVectorContains(closedList, Tile(sf::Vector2i(x, y), newT.GCost + 1, newT.GCost + 1 + GetHCost(Tile(sf::Vector2i(x, y))))))
						{
							openList.push_back(Tile(sf::Vector2i(x, y), newT.GCost + 1, newT.GCost + 1 + GetHCost(Tile(sf::Vector2i(x, y)))));
						}
					}
				}
			}
		}

		map.SetTile(newT.pos, 4);

		std::cout << "openList: " << openList.size() << std::endl;
		std::cout << "closedList: " << closedList.size() << std::endl;
	}
	else
	{
		return;
	}
}

float Pathfinder::GetHCost(Tile pos)
{
	float delX = pos.pos.x - endPos.x;
	float delY = pos.pos.y - endPos.y;

	float d = std::sqrt(std::pow(delX, 2) + std::pow(delY, 2));
	return d;
}

bool Pathfinder::Tile::operator==(Tile rhs)
{
	if (this->cost == rhs.cost && this->GCost == rhs.GCost && this->pos.x == rhs.pos.x && this->pos.y == rhs.pos.y)
		return true;
	return false;
}

bool Pathfinder::Tile::operator!=(Tile rhs)
{
	if (*this == rhs)
		return false;
	return true;
}

void DeleteTileFromVector(std::vector<Pathfinder::Tile> vec, Pathfinder::Tile t)
{
	std::vector<Pathfinder::Tile>::iterator current = vec.begin();
	while (current != vec.end()) {
		if (*current == t) {
			current = vec.erase(current);
		}
		else {
			++current;
		}
	}

}

bool TileVectorContains(std::vector<Pathfinder::Tile> vec, Pathfinder::Tile t)
{
	for (Pathfinder::Tile newT : vec)
	{
		if (newT == t)
		{
			return true;
		}
	}
	return false;
}

bool Pathfinder::inMap(Pathfinder::Tile t)
{
	return inMap(t.pos);
}

bool Pathfinder::inMap(sf::Vector2i pos)
{
	if (pos.x < 0 || pos.y < 0)
		return false;
	if (pos.x > map.getSize().x - 1 || pos.y > map.getSize().y - 1)
		return false;
	return true;
}
