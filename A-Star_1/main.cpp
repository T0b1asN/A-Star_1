#include <iostream>

#include "SFML.h"
#include "curr.h"

#include "Map.h"
#include "Pathfinder.h"

void setup();
void Draw();

Map map(sf::Vector2i(50, 50));
int main()
{
	setup();
	map.setupFromTextPath("res\\Test_2.png");
	Pathfinder pf(map);
	pf.Setup();

	std::cout << "Size: " << map.getSize().x << "|" << map.getSize().y << std::endl;

	std::cout << "Start: " << map.getStartPos().x << "|" << map.getStartPos().y << std::endl;
	std::cout << "End: " << map.getEndPos().x << "|" << map.getEndPos().y << std::endl;

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

		if (steps == 1)
		{
			steps = 0;
			pf.Step();
		}

		//while (!pf.hasPath())
		//	pf.Step();

		Draw();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
		{
			steps++;
		}
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
