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
			if (brightness < 230)
			{
				if (img.getPixel(x, y).r < img.getPixel(x, y).g)
				{
					temp.back() = 2;
				}
				else if (img.getPixel(x, y).r > img.getPixel(x, y).g)
				{
					temp.back() = 3;
				}
			}
		}
		map.at(x) = temp;
	}

	fields.resize(size.x * size.y, sf::RectangleShape());

	int iSt = 0;	//How many Startpositions are found
	int iE = 0;		//How many Endpositions are found

	std::vector<sf::Vector2i> starts;
	std::vector<sf::Vector2i> ends;

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			fields.at(x + y * size.x).setSize(sf::Vector2f(cr::currWin().getSize().x / size.x, cr::currWin().getSize().y / size.y));
			fields.at(x + y * size.x).setPosition(x * (cr::currWin().getSize().x / size.x), y * (cr::currWin().getSize().y / size.y));
			fields.at(x + y * size.x).setFillColor(ColorFromInt(map.at(x).at(y)));

			if (map.at(x).at(y) == 2)		//start
			{
				iSt++;
				starts.push_back(sf::Vector2i(x, y));
			}
			else if (map.at(x).at(y) == 3)	//end
			{
				iE++;
				ends.push_back(sf::Vector2i(x, y));
			}
		}
	}

	if (iSt == 0)
	{
		startPos = sf::Vector2i(0, 0);
		SetTile(startPos, 2);
	}
	else
	{
		startPos = starts.at(0);
		starts.erase(starts.begin());
		for (const sf::Vector2i cPos : starts)
		{
			SetTile(cPos, 0);
		}
	}

	if (iE == 0)
	{
		endPos = size - sf::Vector2i(1, 1);
		SetTile(endPos, 3);
	}
	else
	{
		endPos = ends.back();
		ends.erase(ends.end() - 1);
		for (const sf::Vector2i cPos : ends)
		{
			SetTile(cPos, 0);
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

void Map::SetTile(sf::Vector2i pos, int newValue)
{
	map.at(pos.x).at(pos.y) = newValue;

	fields.at(pos.x + pos.y * size.x).setFillColor(ColorFromInt(map.at(pos.x).at(pos.y)));
}

void Map::SetTile(int indexX, int indexY, int newValue)
{
	SetTile(sf::Vector2i(indexX, indexY), newValue);
}

sf::Color Map::ColorFromInt(int i)
{
	switch (i)
	{
	case 0:
		return sf::Color(200, 200, 200);
		break;
	case 1:
		return sf::Color(0, 0, 0);
		break;
	case 2:
		return sf::Color(0, 255, 0);
		break;
	case 3:
		return sf::Color(255, 0, 0);
		break;
	default:
		std::cout << "Error - Wrong int in map" << std::endl;
		return sf::Color(255, 0, 255);
		break;
	}
}
