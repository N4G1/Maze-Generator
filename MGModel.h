#pragma once
#include <SFML\Graphics.hpp>

class MGModel
{
	sf::RectangleShape* tileArray;
	sf::RectangleShape tile;
	sf::RectangleShape* rectArray;
	sf::RectangleShape rectangle;
	sf::RectangleShape currentRectangle;
	sf::RectangleShape solveShape;
	sf::Color* desiredColor;
	int* walls;
	int rows;
	int columns;
	int tileWidth;
	int currentTile;
	int pathCounter;
	int* pathArray;
	int wallCount;
	int neighborsCounter;
	int* neighbors;
	bool finish;
public:
	MGModel();
	~MGModel();
	void initialize();
	sf::Color getTileColor(int index);
	void setTileColor(int index, sf::Color c);
	void logic();
	void checkNeighbors();
	bool getStatus();
	void draw(sf::RenderWindow & window);
};

