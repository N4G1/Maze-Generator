#include "MGController.h"


MGController::MGController()
{
}

void MGController::initialize()
{
	model.initialize();
	play();
}

void MGController::play()
{
	while (!model.getStatus())
	{
		model.logic();
		view.display();
		time = clock.getElapsedTime();
		std::cout << 1.0f / time.asSeconds() << std::endl;
		//system("cls");
		clock.restart();
	}
	std::cout << "Finish" << std::endl;
	view.reduceFramerate(10);
	while(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		view.display();
}