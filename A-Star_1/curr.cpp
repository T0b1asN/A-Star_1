#include "curr.h"

sf::RenderWindow win;
int width, height;

sf::RenderWindow& cr::currWin()
{
	return win;
}

int cr::getFieldW()
{
	return width;
}

int cr::getFieldH()
{
	return height;
}

void cr::setFieldW(int pWidth)
{
	width = pWidth;
}

void cr::setFieldH(int pHeight)
{
	height = pHeight;
}
