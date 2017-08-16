#include "MGView.h"
MGModel model;

MGView::MGView()
{
	window.create(sf::VideoMode(500, 500), "Maze Generator"); //creating window
	//window.setFramerateLimit(10); //caping the framerate
}

void MGView::reduceFramerate(int fps)
{
	window.setFramerateLimit(fps);
}

void MGView::display()
{
	if (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		model.draw(window);
		window.display();
	}
}