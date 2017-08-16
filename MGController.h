#pragma once
#include <iostream>
#include "MGView.h"
extern MGModel model;

class MGController
{
	sf::Time time;
	sf::Clock clock;
	MGView view;
public:
	MGController();
	void initialize();
	void play();
};

