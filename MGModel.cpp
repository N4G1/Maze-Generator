#include "MGModel.h"


MGModel::MGModel()
{
	rows = 40;
	columns = 40;
	tileWidth = 500/rows;
	wallCount = rows*(rows + 1) * 2;
	tileArray = new sf::RectangleShape[rows*columns];
	rectArray = new sf::RectangleShape[wallCount];
	pathArray = new int[rows*columns];
	walls = new int[wallCount];
	desiredColor = new sf::Color(0,255,255);
	neighbors = new int[4];
	srand(time(nullptr));
	currentTile = 0; //start tile index
	pathCounter = 0;
}

MGModel::~MGModel()
{
	delete[] tileArray;
	delete[] rectArray;
	delete[] pathArray;
	delete[] neighbors;
	delete[] walls;
}

void MGModel::initialize()
{
	finish = false;

	for (int i = 0; i < wallCount; i++)
		walls[i] = true;

	//when a tile has no more neighbors this array will be used to find a tile with neighbors
	for (int i = 0; i < rows*columns; i++)
		pathArray[i] = -1;

	//Creating tiles
	int counter = 0;
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < columns; i++)
		{
			tileArray[counter] = tile;
			tileArray[counter].setSize(sf::Vector2f(tileWidth, tileWidth));
			tileArray[counter].setPosition(sf::Vector2f(i*tileWidth + 5, j*tileWidth + 5));
			counter++;
		}
	}

	//Creating horizontal walls
	int counter1 = 0;
	for (int j = 0; j < rows+1; j++)
	{
		for (int i = 0; i < columns; i++)
		{
			rectArray[counter1] = rectangle;
			rectArray[counter1].setPosition(sf::Vector2f(i*tileWidth + 5, j*tileWidth + 5));
			rectArray[counter1].setSize(sf::Vector2f(tileWidth, 2));
			rectArray[counter1].setFillColor(sf::Color::Red);
			counter1++;
		}
	}

	//Creating vertical walls
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < columns + 1; i++)
		{
			rectArray[counter1] = rectangle;
			rectArray[counter1].setPosition(sf::Vector2f(i*tileWidth + 5, j*tileWidth + 5));
			rectArray[counter1].setSize(sf::Vector2f(2, tileWidth));
			rectArray[counter1].setFillColor(sf::Color::Red);
			counter1++;
		}
	}
	setTileColor(currentTile, *desiredColor);
}

sf::Color MGModel::getTileColor(int index)
{
	return tileArray[index].getFillColor();
}

void MGModel::setTileColor(int index, sf::Color c)
{
	tileArray[index].setFillColor(c);
}

void MGModel::logic()
{
	const int MAXNEIGHBORS = 4;
	int temp[MAXNEIGHBORS];
	int randomNeighbor;
	int counter = 0;
	neighborsCounter = 0;
	
	for (int i = 0; i < MAXNEIGHBORS; i++)
		neighbors[i] = -1;

	//checking how many neighbors current tile has
	checkNeighbors();

	//Sorting array in ascending order
	std::sort(&neighbors[0], &neighbors[MAXNEIGHBORS]);

	//Reversing the order
	for (int i = MAXNEIGHBORS - 1; i >= 0; i--)
		temp[counter++] = neighbors[i];

	//When current tile has neighbors
	if (neighborsCounter != 0)
	{
		//picking random neighbor
		randomNeighbor = rand() % neighborsCounter;
		setTileColor(temp[randomNeighbor], *desiredColor);
		
		//"DELETING" TOP WALL
		if ((currentTile - temp[randomNeighbor]) > 1)
			walls[currentTile] = false;

		//"DELETING" RIGHT WALL
		if ((currentTile - temp[randomNeighbor]) == -1)
			walls[(rows*rows) + rows + currentTile + (currentTile / rows) + 1] = false;
		
		//"DELETING" BOTTOM WALL
		if ((currentTile - temp[randomNeighbor]) < -1)
			walls[temp[randomNeighbor]] = false;

		//"DELETING" LEFT WALL
		if ((currentTile - temp[randomNeighbor]) == 1)
			walls[(rows*rows) + rows + currentTile + (currentTile / rows)] = false;
		
		currentTile = temp[randomNeighbor];
		pathArray[pathCounter++] = currentTile;
	}

	//When current tile has no neighbors
	else
	{
		for (int i = (rows*columns) - 1; i >= 0; i--)
		{
			if (pathArray[i] != -1)
			{
				currentTile = pathArray[i];
				pathArray[i] = -1;
				return;
			}
		}
		finish = true;
	}
}

void MGModel::checkNeighbors()
{
	if (currentTile - columns > 0)
	{
		if (tileArray[currentTile - columns].getFillColor() != *desiredColor)
		{
			neighbors[0] = currentTile - columns;
			neighborsCounter++;
		}
	}
	if (tileArray[currentTile + 1].getFillColor() != *desiredColor && ((currentTile + 1) % columns != 0))
	{
		neighbors[1] = currentTile + 1;
		neighborsCounter++;
	}
	if ((currentTile + columns) < (columns*rows))
	{
		if (tileArray[currentTile + columns].getFillColor() != *desiredColor)
		{
			neighbors[2] = currentTile + columns;
			neighborsCounter++;
		}
	}
	if (currentTile != 0)
	{
		if (tileArray[currentTile - 1].getFillColor() != *desiredColor && ((currentTile - 1) % columns != (columns - 1)))
		{
			neighbors[3] = currentTile - 1;
			neighborsCounter++;
		}
	}
}

bool MGModel::getStatus()
{
	return finish;
}

void MGModel::draw(sf::RenderWindow &window)
{
	//Drawing tiles
	for (int i = 0; i < rows*rows; i++)
		window.draw(tileArray[i]);
	
	//Drawing walls
	for (int i = 0; i < wallCount; i++)
	{
		if(walls[i] == true)
			window.draw(rectArray[i]);
	}
}