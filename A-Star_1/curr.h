#pragma once
#include "SFML.h"

#define DIAGONAL true

namespace cr
{
	sf::RenderWindow& currWin();
	int getFieldW();
	int getFieldH();
	void setFieldW(int pWidth);
	void setFieldH(int pHeight);
}
