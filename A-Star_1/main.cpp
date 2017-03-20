#include <iostream>

#include "SFML.h"
#include "curr.h"

#include "Map.h"
#include "Pathfinder.h"
#include "Map2_0.h"

void setup();
void Draw();

Map2_0 map;

//Convert point on the map (like {10, 10}) to a "world point" that can be drawn
//returns center of the field
sf::Vector2f mapPointToWorldPoint(sf::Vector2i in)
{
	return sf::Vector2f(sf::Vector2f(in * cr::getFieldW()) + sf::Vector2f(cr::getFieldW() / 2.f, cr::getFieldH() / 2.f));
}

//Draws a line over the path
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
	std::string name;
	std::cout << "Type in name of the image in the res folder (w/ extension): " << std::endl;
	std::cin >> name;

	std::cout << "Allow diagonal movement (Y/N)" << std::endl;
	char answ = ' ';
	std::cin >> answ;
	switch (answ)
	{
	case 'y':
	case 'Y':
		cr::setDiag(true);
		break;
	case 'n':
	case 'N':
		cr::setDiag(false);
		break;
	}

	setup();
	sf::Image img;
	if (!img.loadFromFile("res\\" + name))
	{
		std::cout << "File not found!" << std::endl;
		std::system("PAUSE");
		return 1;
	}
	map.setupFromImage(img);

	Pathfinder pf(map);

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
			if (evnt.type == sf::Event::Closed)
				return 0;
		Draw();	
	}

	std::system("Pause");
	return 0;
}

//sets up the window
void setup()
{
	cr::currWin().create(sf::VideoMode(750U, 750U), "A* Test", sf::Style::Close);
	cr::currWin().setFramerateLimit(60);
	cr::currWin().setKeyRepeatEnabled(false);
}

//Draws everything in the window
void Draw()
{
	cr::currWin().clear(sf::Color(100, 100, 100));
	map.Draw();
	DrawPath();
	cr::currWin().display();
}
