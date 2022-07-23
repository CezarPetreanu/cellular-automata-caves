#include "Platform/Platform.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_grid(int grid[60][60]);
int get_grid_sum(int grid[60][60], int i, int j);
void apply_cellular(int grid[60][60]);

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

	// init grid
	int grid[60][60];
	init_grid(grid);

	// drawing
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(10.f, 10.f));
	rect.setFillColor(sf::Color(255, 255, 0));

	int current_key_cellular = 0;
	int previous_key_cellular = 0;
	int current_key_reset = 0;
	int previous_key_reset = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// press Q to apply cellular
		previous_key_cellular = current_key_cellular;
		current_key_cellular = (GetAsyncKeyState('Q') & 0x8000);

		if (previous_key_cellular == 0 && current_key_cellular != 0)
			apply_cellular(grid); // apply cellular

		// press R to reset grid
		previous_key_reset = current_key_reset;
		current_key_reset = (GetAsyncKeyState('R') & 0x8000);

		if (previous_key_reset == 0 && current_key_reset != 0)
			init_grid(grid); // reset

		window.clear();
		//DRAW STUFF HERE

		for (int i = 0; i < 60; i++)
			for (int j = 0; j < 60; j++)
				if (grid[i][j])
				{
					rect.setPosition(sf::Vector2f(20.f + i * 10, 20.f + j * 10));
					window.draw(rect);
				}

		//END
		window.display();
	}

	return 0;
}

void init_grid(int grid[60][60])
{
	for (int i = 0; i < 60; i++)
		for (int j = 0; j < 60; j++)
			grid[i][j] = (rand() % 2) * (i > 0 && i < 59 && j > 0 && j < 59);
}

int get_grid_sum(int grid[60][60], int i, int j)
{
	int s = 0;
	for (int ii = i - 1; ii <= i + 1; ii++)
		for (int jj = j - 1; jj <= j + 1; jj++)
			s += grid[ii][jj];
	return s;
}

void apply_cellular(int grid[60][60])
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