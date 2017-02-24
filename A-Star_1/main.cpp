#include <iostream>

#include "SFML.h"
#include "curr.h"

#include "Map.h"
#include "Pathfinder.h"
#include "Map2_0.h"

void setup();
void Draw();

Map2_0 map;

int main()
{
	setup();
	sf::Image img;
	if (!img.loadFromFile("res\\Test_2.png"))
		return 0;
	Map2_0 _map(img);
	map = _map;

	Pathfinder pf(map);

	std::cout << "Size: " << map.getSize().x << "|" << map.getSize().y << std::endl;

	std::cout << "Start: " << map.getStart().x << "|" << map.getStart().y << std::endl;
	std::cout << "End: " << map.getEnd().x << "|" << map.getEnd().y << std::endl;

	int steps = 0;
	int stepsize = 1;

	while (cr::currWin().isOpen())
	{
		sf::Event evnt;
		while (cr::currWin().pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:

				return 0;
				break;
			}
		}

		pf.Step();

		Draw();
	}

	std::system("Pause");
	return 0;
}

void setup()
{
	cr::currWin().create(sf::VideoMode(750U, 750U), "A* Test", sf::Style::Close);
	cr::currWin().setFramerateLimit(60);
}

void Draw()
{
	cr::currWin().clear(sf::Color(100, 100, 100));
	map.Draw();
	cr::currWin().display();
}
