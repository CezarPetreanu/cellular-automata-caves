#include "Platform/Platform.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 120

int** init_grid(int grid_size);
void reset_grid(int** grid);
int get_grid_sum(int** grid, int i, int j);
void apply_cellular(int** grid);

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Running." << std::endl;
#endif

	// init window
	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 700), "cellular-automata-caves", sf::Style::Titlebar | sf::Style::Close);
	platform.setIcon(window.getSystemHandle());

	sf::Event event;

	// init random
	srand(time(NULL));

	// init grid
	int** grid = init_grid(SIZE);
	reset_grid(grid);

	// drawing
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(5.f, 5.f));
	rect.setFillColor(sf::Color(255, 255, 0));

	sf::Font font;
	if (!font.loadFromFile("src\\res\\arial.ttf"))
		std::cout << "ERROR: Font file not found.\n";
	sf::Text text_instructions;
	text_instructions.setFont(font);
	text_instructions.setCharacterSize(20);
	text_instructions.setPosition(25.f, 625.f);
	text_instructions.setString("Q - Next step\nR - Reset");

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

		window.clear();

		// key inputs
		// press Q to apply cellular
		previous_key_cellular = current_key_cellular;
		current_key_cellular = (GetAsyncKeyState('Q') & 0x8000);

		if (previous_key_cellular == 0 && current_key_cellular != 0)
			apply_cellular(grid); // apply cellular

		// press R to reset grid
		previous_key_reset = current_key_reset;
		current_key_reset = (GetAsyncKeyState('R') & 0x8000);

		if (previous_key_reset == 0 && current_key_reset != 0)
			reset_grid(grid); // reset

		//DRAW STUFF HERE

		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (grid[i][j])
				{
					rect.setPosition(sf::Vector2f(20.f + i * 5, 20.f + j * 5));
					window.draw(rect);
				}
		window.draw(text_instructions);
		//END
		window.display();
	}

	return 0;
}

int** init_grid(int grid_size)
{
	int** grid = new int*[grid_size];
	for (int i = 0; i < grid_size; i++)
		grid[i] = new int[grid_size];

	return grid;
}

void reset_grid(int** grid)
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			grid[i][j] = (rand() % 2) * (i > 0 && i < SIZE - 1 && j > 0 && j < SIZE - 1);
}

int get_grid_sum(int** grid, int i, int j)
{
	int s = 0;
	for (int ii = i - 1; ii <= i + 1; ii++)
		for (int jj = j - 1; jj <= j + 1; jj++)
			s += grid[ii][jj];
	return s;
}

void apply_cellular(int** grid)
{
	int** grid_copy = init_grid(SIZE);
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			grid_copy[i][j] = (get_grid_sum(grid, i, j) > 4);
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
		for (int j = 1; j < SIZE - 1; j++)
			grid[i][j] = grid_copy[i][j];
}