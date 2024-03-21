#include "demineur.h"

void game_over(c_square grid[NUMBER_Y][NUMBER_X])
{
	for (int i = 0; i < NUMBER_Y;i++)
	{
		for (int j = 0; j < NUMBER_X; j++)
		{
			if (grid[i][j].type == BOMB)
				grid[i][j].revealed = true;
		}
	}
}

void set_number_bombs(c_square grid[NUMBER_Y][NUMBER_X])
{
	for (int i = 0; i < NUMBER_Y; i++)
	{
		for (int j = 0; j < NUMBER_X; j++)
		{
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					if (x+i >= 0 && x+i < NUMBER_Y && y+j >= 0 && y+j < NUMBER_X)
					{
						if (grid[i+x][j+y].type == BOMB)
							grid[i][j].bombAround++;
						assert(grid[i][j].bombAround <= 8);
					}
				}
			}
		}
	}
}
// TODO: track the number of tiles getting revealed to change sound
void cascade_click(c_square grid[NUMBER_Y][NUMBER_X], int x, int y)
{
	if (grid[x][y].type == BOMB)
		return ;
	if (grid[x][y].bombAround != 0)
		return ;
	int i = -1;
	int j = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (x+i >= 0 && x+i < NUMBER_Y && y+j >= 0 && y+j < NUMBER_X)
			{
				if (grid[x+i][y+j].type != BOMB && !grid[x+i][y+j].clicked)
				{
					grid[x+i][y+j].clicked = true; 
					cascade_click(grid, x+i, y+j);
				}
			}
			j++;
		}
		i++;
	}
}

void reset_game(c_square grid[NUMBER_Y][NUMBER_X])
{
	for (int y = 0; y < NUMBER_Y;y++)
	{
		for (int x = 0; x < NUMBER_X; x++)
		{
			(grid)[y][x].dimensions = 
				(Rectangle){x*RECT_SIZE, y*RECT_SIZE + 100, RECT_SIZE, RECT_SIZE};
			(grid)[y][x].type = EMPTY;
			(grid)[y][x].bombAround = 0;
			(grid)[y][x].clicked = false;
			(grid)[y][x].hovered = false;
			(grid)[y][x].flagged = false;
			(grid)[y][x].revealed = false;
			(grid)[y][x].half = false;
		}
	}
	set_mines(grid);
	set_number_bombs(grid);
}
