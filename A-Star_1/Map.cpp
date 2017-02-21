#include "Map.h"

Map::Map(sf::Vector2i pSize)
{
	size = pSize;
}

void Map::priv_setup()
{
	fields.resize(size.x * size.y, sf::RectangleShape());

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			fields.at(x + y * size.x).setSize(sf::Vector2f(cr::currWin().getSize().x / size.x, cr::currWin().getSize().y / size.y));
			fields.at(x + y * size.x).setPosition(x * (cr::currWin().getSize().x / size.x), y * (cr::currWin().getSize().y / size.y));
			fields.at(x + y * size.x).setFillColor(sf::Color(0, 0, std::rand() % 255));
		}
	}
}

void Map::setup()
{
	for (int x = 0; x < size.x; x++)
	{
		std::vector<int> temp;
		for (int y = 0; y < size.y; y++)
		{
			temp.push_back(0);
		}
		map.push_back(temp);
	}

	//priv_setup();
}

Map::~Map()
{

}

void Map::Draw()
{
	for (int i = 0; i < fields.size(); i++)
	{
		cr::currWin().draw(fields.at(i));
	}
}

void Map::setupFromTexture(sf::Image img)
{
	setup();

	size = sf::Vector2i(img.getSize().x, img.getSize().y);

	for (int x = 0; x < size.x; x++)
	{
		std::vector<int> temp;
		for (int y = 0; y < size.y; y++)
		{
			temp.push_back(0);
			int brightness = (0.2126 * img.getPixel(x, y).r + 0.7152 * img.getPixel(x, y).g + 0.0722 * img.getPixel(x, y).b);
			if (brightness > 55)
			{
				temp.back() = 0;
			}
			else if (brightness < 55)
			{
				temp.back() = 1;
			}
		}
		map.at(x) = temp;
	}

	fields.resize(size.x * size.y, sf::RectangleShape());

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			fields.at(x + y * size.x).setSize(sf::Vector2f(cr::currWin().getSize().x / size.x, cr::currWin().getSize().y / size.y));
			fields.at(x + y * size.x).setPosition(x * (cr::currWin().getSize().x / size.x), y * (cr::currWin().getSize().y / size.y));
			if (map.at(x).at(y) == 0)
			{
				fields.at(x + y * size.x).setFillColor(sf::Color(255, 255, 255));
			}
			else if (map.at(x).at(y) == 1)
			{
				fields.at(x + y * size.x).setFillColor(sf::Color(0, 0, 0));
			}
		}
	}
}

void Map::setupFromTextPath(std::string path)
{
	sf::Image tmp;
	if (tmp.loadFromFile(path))
		setupFromTexture(tmp);
	else
		std::cout << "Error loading file" << std::endl;
	return;
}
