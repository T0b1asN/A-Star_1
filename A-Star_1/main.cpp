#include <iostream>

#include "SFML.h"
#include "curr.h"

#include "Map.h"
#include "Pathfinder.h"
#include "Map2_0.h"

void setup();
void Draw();

Map2_0 map;

sf::Vector2f mapPointToWorldPoint(sf::Vector2i in)
{
	return sf::Vector2f(sf::Vector2f(in * cr::getFieldW()) + sf::Vector2f(cr::getFieldW() / 2.f, cr::getFieldH() / 2.f));
}

void DrawPath()
{
	sf::VertexArray line(sf::PrimitiveType::LineStrip);
	for (const sf::Vector2i v : map.getPath())
	{
		line.append(sf::Vertex(mapPointToWorldPoint(v), sf::Color(0, 0, 255)));
	}
	cr::currWin().draw(line);
}

int main()
{
	setup();
	sf::Image img;
	if (!img.loadFromFile("res\\genmaze.png"))
		return 0;
	map.setupFromImage(img);

	Pathfinder pf(map);
	std::cout << "Size: " << map.getSize().x << "|" << map.getSize().y << std::endl;

	std::cout << "Start: " << map.getStart().x << "|" << map.getStart().y << std::endl;
	std::cout << "End: " << map.getEnd().x << "|" << map.getEnd().y << std::endl;
	sf::Clock c;
	if (pf.Eff_Solve() == 1)
	{
		pf.reconstructPath(map.getStart(), map.getEnd());
		map.setPath(pf.getPath());
	}
	else
		std::cout << "No Solution!!!" << std::endl;
	
	std::cout << "Time: " << c.getElapsedTime().asSeconds() << std::endl;

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
			case sf::Event::KeyPressed:
				//if (evnt.key.code == sf::Keyboard::Add)
				//	if (!pf.isFinished())
				//		pf.Step();
				//	else
				//		std::cout << "finished" << std::endl;

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
	cr::currWin().setKeyRepeatEnabled(false);
}

void Draw()
{
	cr::currWin().clear(sf::Color(100, 100, 100));
	map.Draw();
	DrawPath();
	cr::currWin().display();
}
