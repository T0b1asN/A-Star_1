#pragma once
#include "SFML.h"
#include "curr.h"
#include "Map.h"

#include <iostream>
#include <vector>


class Pathfinder
{
public:
	class Tile
	{
	public:
		Tile(sf::Vector2i pPos, int _gcost, float _cost)
		{
			pos = pPos;
			GCost = _gcost;
			cost = _cost;
		}

		Tile(sf::Vector2i pPos, int _gcost)
		{
			pos = pPos;
			GCost = _gcost;
			cost = 1000.0f;
		}

		Tile(sf::Vector2i pPos)
		{
			pos = pPos;
			GCost = 1000;
			cost = 1000.0f;
		}

		Tile()
		{
			pos = sf::Vector2i(0, 0);
			GCost = 1000;
			cost = 1000.0f;
		}

		sf::Vector2i pos;
		int GCost;
		float cost;

		bool operator==(Tile& rhs);
		bool operator!=(Tile& rhs);

		friend std::ostream& operator<< (std::ostream& stream, const Tile& t) 
		{
			stream << "Pos: " << t.pos.x << "|" << t.pos.y << " ; Cost: " << t.cost;
			return stream;
		}
	};
private:
	Map& map;

	Tile currPos;

	sf::Vector2i startPos;
	sf::Vector2i endPos;

	std::vector<Tile> openList;
	std::vector<Tile> closedList;

	float GetHCost(Tile pos);
public:
	Pathfinder(Map& pMap);
	~Pathfinder();

	void Setup();
	void Step();
};

void DeleteTileFromVector(std::vector<Pathfinder::Tile> vec, Pathfinder::Tile t);
