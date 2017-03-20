#include "Map2_0.h"

Map2_0::Map2_0()
{

}

Map2_0::Map2_0(std::string textPath)
{
	
}

Map2_0::Map2_0(sf::Image img)
{
	//setup();
	size = sf::Vector2i(img.getSize().x, img.getSize().y);

	cr::setFieldW(cr::currWin().getSize().x / size.x);
	cr::setFieldH(cr::currWin().getSize().y / size.y);

	int iSt = 0;	//How many Startpositions are found
	int iE = 0;		//How many Endpositions are found

	std::vector<sf::Vector2i> starts;
	std::vector<sf::Vector2i> ends;

	for (int x = 0; x < size.x; x++)
	{
		std::vector<Node> temp;
		for (int y = 0; y < size.y; y++)
		{
			temp.push_back(Node(sf::Vector2i(x, y)));
			temp.back().addNbs(*this);

			sf::Color pix = img.getPixel(x, y);
			if (pix == sf::Color::Black)
			{
				temp.back().setObstacle(true);
				temp.back().debCol = sf::Color::Black;
			}
			else
			{
				if (pix.g > pix.r) //gruen
				{
					iSt++;
					starts.push_back(sf::Vector2i(x, y));
					temp.back().debCol = sf::Color::Green;
				}
				else if (pix.r > pix.g) //rot
				{
					iE++;
					ends.push_back(sf::Vector2i(x, y));
					temp.back().debCol = sf::Color::Red;
				}
			}
		}
		nodes.push_back(temp);
	}

	if (iSt == 0)
		start = sf::Vector2i(0, 0);
	else
		start = starts.at(0);

	if (iE == 0)
		end = size - sf::Vector2i(1, 1);
	else
		end = ends.back();


	for (std::vector<Node> vec : nodes)
	{
		for (Node n : vec)
		{
			n.addNbs(*this);
		}
	}
}

Map2_0::~Map2_0()
{

}

void Map2_0::Draw()
{
	for (std::vector<Node>& vec : nodes)
	{
		for (Node& n : vec)
		{
			n.Draw();
		}
	}
}

void Map2_0::PrintSize()
{
	std::cout << "Mapsize: " << nodes.size() << " | " << nodes.at(0).size() << std::endl;
}

void Map2_0::setupFromImage(sf::Image img)
{
	nodes.clear();
	//setup();
	size = sf::Vector2i(img.getSize().x, img.getSize().y);

	cr::setFieldW(cr::currWin().getSize().x / size.x);
	cr::setFieldH(cr::currWin().getSize().y / size.y);

	int iSt = 0;	//How many Startpositions are found
	int iE = 0;		//How many Endpositions are found

	std::vector<sf::Vector2i> starts;
	std::vector<sf::Vector2i> ends;

	for (int x = 0; x < size.x; x++)
	{
		std::vector<Node> temp;
		for (int y = 0; y < size.y; y++)
		{
			temp.push_back(Node(sf::Vector2i(x, y)));
			temp.back().addNbs(*this);

			sf::Color pix = img.getPixel(x, y);
			if (pix == sf::Color::Black)
			{
				temp.back().setObstacle(true);
				temp.back().debCol = sf::Color::Black;
			}
			else
			{
				if (pix.g > pix.r) //gruen
				{
					iSt++;
					starts.push_back(sf::Vector2i(x, y));
				}
				else if (pix.r > pix.g) //rot
				{
					iE++;
					ends.push_back(sf::Vector2i(x, y));
				}
			}
		}
		nodes.push_back(temp);
	}

	if (iSt == 0)
		start = sf::Vector2i(0, 0);
	else
		start = starts.at(0);

	if (iE == 0)
		end = size - sf::Vector2i(1, 1);
	else
		end = ends.back();

	nodes.at(start.x).at(start.y).debCol = sf::Color::Green;
	nodes.at(end.x).at(end.y).debCol = sf::Color::Red;

	for (std::vector<Node>& vec : nodes)
	{
		for (Node& n : vec)
		{
			n.addNbs(*this);
			//std::cout << "Neighbourcount at start: " << n.getNbs().size() << std::endl;
		}
	}
}
