#include "Pathfinder.h"

Pathfinder::Pathfinder(Map pMap) :
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
	Step();
}

void Pathfinder::Step()
{
	int currGCost = currPos.GCost;
	closedList.push_back(currPos);

	for (int x = currPos.pos.x - 1; x < currPos.pos.x + 1; x++)
	{
		for (int y = currPos.pos.y - 1; y < currPos.pos.y + 1; y++)
		{
			if (x > 0 && y > 0 && x < map.getSize().x && y < map.getSize().y)
			{
				if ((sf::Vector2i(x, y) != currPos.pos)) // Ecken?? kostet mehr??
				{
					std::cout << currPos.pos.x << "|" << currPos.pos.y << std::endl;
					if (map.map.at(x).at(y) != 1)
					{
						//if (std::find(v.begin(), v.end(), x) != v.end()) {
						//	/* v contains x */
						//}
						//else {
						//	/* v does not contain x */
						//}
						bool isFree = true;
						for (const Tile t : closedList)
						{
							if (t.pos == sf::Vector2i(x, y))
								isFree = false;
						}
						if (isFree)
						{
							Tile t = Tile(sf::Vector2i(x, y), currGCost + 1, currGCost + 1 + GetHCost(Tile(sf::Vector2i(x, y))));
							bool inOpen = false;
							for (const Tile p : openList)
							{
								if (p.pos == t.pos)
									inOpen = true;
							}
							if (!inOpen)
							{
								openList.push_back(t);
							}
						}
					}
				}
			}
		}
	}

	Tile record(sf::Vector2i(0, 0), 10000, 10000.0f);

	for (const Tile t : openList)
	{
		if (t.cost < record.cost)
		{
			record = t;
		}
	}

	DeleteTileFromVector(closedList, currPos);
	std::cout << "record: " << record.pos.x << "|" << record.pos.y << std::endl;
	currPos = record;

	map.SetTile(currPos.pos, 4);
}

float Pathfinder::GetHCost(Tile pos)
{
	float delX = pos.pos.x - endPos.x;
	float delY = pos.pos.y - endPos.y;

	float d = std::sqrt(std::pow(delX, 2) + std::pow(delY, 2));
	std::cout << d << std::endl;
	return d;
}

bool Pathfinder::Tile::operator==(Tile& rhs)
{
	if (this->cost == rhs.cost && this->GCost == rhs.GCost && this->pos.x == rhs.pos.x && this->pos.y == rhs.pos.y)
		return true;
}

bool Pathfinder::Tile::operator!=(Tile& rhs)
{
	if (*this == rhs)
		return false;
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
