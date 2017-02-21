#include <iostream>

#include "SFML.h"
#include "curr.h"

#include "Map.h"

void setup();
void Draw();

Map map(sf::Vector2i(50, 50));
int main()
{
	setup();
	map.setupFromTextPath("res\\Test_2.png");

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
