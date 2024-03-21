#include "demineur.h"

bool is_inBounds(c_square (grid)[NUMBER_Y][NUMBER_X], Vector2 mousePosition,
		int col, int row)
{
	int s_height = GRID_HEIGHT;
	if (col >= 0 && col < NUMBER_X && row >= 0 && row < NUMBER_Y 
			&& mousePosition.x >= col * (GRID_WIDTH / (float)NUMBER_X) + 5
			&& mousePosition.x < (col + 1) * (GRID_WIDTH / (float)NUMBER_X) - 5
			&& mousePosition.y >= ((row + 0)* (s_height / (float)NUMBER_Y) + 5)
			&& mousePosition.y < ((row + 1) * (s_height / (float)NUMBER_Y) - 5))
	{
		return true;
	}
	return false;
}

Vector2 get_rect_mouse(c_square (grid)[NUMBER_Y][NUMBER_X],
		Vector2 mousePosition)
{
    int col = (int)(mousePosition.x / (GRID_WIDTH / (float)NUMBER_X));
    int row = (int)(mousePosition.y / (GRID_HEIGHT / (float)NUMBER_Y));
	if (col >= NUMBER_X || col < 0 || row >= NUMBER_Y || row < 0)
		return (Vector2){-1, -1};

	 if (is_inBounds(grid, mousePosition, col, row))
		 return (Vector2){row, col};
	 return (Vector2){-1, -1};
}

Vector2 is_mouse_rect_half(c_square (grid)[NUMBER_Y][NUMBER_X],
		Vector2 mousePosition)
{
    int col = (int)(mousePosition.x / (GRID_WIDTH / (float)NUMBER_X));
    int row = (int)(mousePosition.y / (GRID_HEIGHT / (float)NUMBER_Y));

	if (col >= NUMBER_X || col < 0 || row >= NUMBER_Y || row < 0)
		return (Vector2){-1, -1};

	if (is_inBounds(grid, mousePosition, col, row))
	{
		(grid)[row][col].half = true;
		 return (Vector2){row, col};
	}
	return (Vector2){-1, -1};
}

void is_hovered_rect(c_square grid[NUMBER_Y][NUMBER_X], Vector2 mousePosition, bp *old)
{
	int col = (int)(mousePosition.x / (GRID_WIDTH / (float)NUMBER_X));
	int row = (int)(mousePosition.y / (GRID_HEIGHT / (float)NUMBER_Y));
	if (col >= NUMBER_X || col < 0 || row >= NUMBER_Y || row < 0)
		return ;
	
	if ((is_inBounds(grid, mousePosition, col, row)))
	{
		if (!grid[row][col].hovered && !grid[row][col].clicked && !grid[row][col].flagged && !grid[row][col].revealed)
		{
			if (!IsSoundPlaying(soundArray[currentSound]))
			{
				PlaySound(soundArray[currentSound]);
				currentSound++;
			}
			if (currentSound >= MAX_SOUNDS)
				currentSound = 0;
			SetMouseCursor(4);
			grid[row][col].hovered = true;
			if (row == old->row && col == old->col)
				return;
			if (old->row >= 0 && old->col >= 0 && old->row < NUMBER_Y && old->col < NUMBER_X )
				grid[old->row][old->col].hovered = false;
			old->row = row;
			old->col = col;
		}
	}
	else
	{
		SetMouseCursor(0);
		grid[row][col].hovered = false;
		if (old->row >= 0 && old->col >= 0 && old->row < NUMBER_Y && old->col < NUMBER_X)
			grid[old->row][old->col].hovered = false;
	}
}
