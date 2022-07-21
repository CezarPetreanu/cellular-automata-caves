// 21/07/2022 WARNING: CELLULAR AUTOMATA ALGORITHM NOT WORKING PROPERLY!

#include "Platform/Platform.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_grid_sum(int grid[60][60], int i, int j);

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Running." << std::endl;
#endif

	// init window
	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 640), "cellular-automata-caves", sf::Style::Titlebar | sf::Style::Close);
	platform.setIcon(window.getSystemHandle());

	sf::Event event;

	// init random
	srand(time(NULL));

	// init data grid
	int grid[60][60] = { 0 };
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 60; j++)
			grid[i][j] = rand() % 2;

	// apply cellular
	int reps = 5;
	for (int r = 0; r < reps; r++)
	{
		int grid_copy[60][60] = { 0 };
		for (int i = 1; i < 59; i++)
		{
			for (int j = 1; j < 59; j++)
			{
				if (get_grid_sum(grid, i, j) > 4)
					grid_copy[i][j] = 1;
			}
		}

		for (int i = 1; i < 59; i++)
			for (int j = 1; j < 59; j++)
				grid[i][j] = grid_copy[i][j];
	}

	// init drawing rectangles
	sf::RectangleShape rect[60][60];
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 60; j++)
		{
			if (grid[i][j])
			{
				rect[i][j].setPosition(sf::Vector2f(20.f + i * 10, 20.f + j * 10));
				rect[i][j].setSize(sf::Vector2f(10.f, 10.f));
				rect[i][j].setFillColor(sf::Color(255, 255, 0));
			}
		}

	// drawing
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//DRAW STUFF HERE

		for (int i = 0; i < 60; i++)
			for (int j = 0; j < 60; j++)
				if (grid[i][j])
					window.draw(rect[i][j]);

		//END
		window.display();
	}

	return 0;
}

int get_grid_sum(int grid[60][60], int i, int j)
{
	int s = 0;
	for (int ii = i - 1; ii <= i + 1; ii++)
		for (int jj = j - 1; jj <= j + 1; jj++)
			s += grid[ii][jj];
	return s;
}
