#pragma once
//A file that keeps track of the current stuff, like the active window
#include "SFML.h"

//Determines, if diagonal movement is allowed
namespace cr
{
	sf::RenderWindow& currWin();
	int getFieldW();
	int getFieldH();
	void setFieldW(int pWidth);
	void setFieldH(int pHeight);

	bool getDiag();
	void setDiag(bool d);
}
