#pragma once
#include "MGModel.h"

class MGView
{
	sf::RenderWindow window;
public:
	MGView();
	void reduceFramerate(int fps);
	void display();
};

