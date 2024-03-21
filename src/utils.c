#include "demineur.h"
#include <stdio.h>

void *init_squares(void)
{
  	c_square(*squares)[NUMBER_X] = malloc(sizeof(c_square[NUMBER_Y][NUMBER_X]));
	int x = 0; int y = 0;
	while (y < NUMBER_Y)
	{
		x = 0;
		while (x < NUMBER_X)
		{
			(squares)[y][x].dimensions = 
				(Rectangle){x*RECT_SIZE, y*RECT_SIZE+100, RECT_SIZE, RECT_SIZE};
			(squares)[y][x].type = EMPTY;
			(squares)[y][x].bombAround = 0;
			(squares)[y][x].clicked = false;
			(squares)[y][x].hovered = false;
			(squares)[y][x].flagged = false;
			(squares)[y][x].anim = false;
			(squares)[y][x].anim2 = false;
			(squares)[y][x].revealed = false;
			(squares)[y][x].half = false;
			(squares)[y][x].scale = 0.0f;
			(squares)[y][x].current_frame = 35;
			x++;
		}
		y++; 
	}
	return squares;
}

void init_camera(Camera2D *camera)
{
	camera->zoom = 1;
	camera->target = (Vector2){TARGET_X, TARGET_Y}; 
	camera->offset = (Vector2){OFFSET_X, OFFSET_Y};
	camera->zoom = ZOOM; camera->rotation = ROTATION;
}

void set_mines(c_square grid[NUMBER_Y][NUMBER_X])
{
	int i = 0;
	while (i < TOTAL_MINES)
	{
		int randomTile = GetRandomValue(0, TOTAL_R-1);
		int x = randomTile % NUMBER_X;
		int y = randomTile / NUMBER_X;
		if (grid[y][x].type != BOMB)
		{
			grid[y][x].type = BOMB;
			i++;
		}
	}
}
//TODO: add volume control / fx disabled
//here some sounds are global others aren't .. Why ? I don't even know.
void set_sound(c_square grid[NUMBER_Y][NUMBER_Y])
{
	grid[0][0].sound->boom = LoadSound("son/test.mp3");
	grid[0][0].sound->success[0] = LoadSound("son/success.wav");
	grid[0][0].sound->success[1] = LoadSound("son/success2.wav");
	grid[0][0].sound->success[2] = LoadSound("son/success3.wav");
	grid[0][0].sound->success[3] = LoadSound("son/success4.wav");
	grid[0][0].sound->success[4] = LoadSound("son/success5.wav");
	grid[0][0].sound->flag = LoadSound("son/flag_double.wav");
	grid[0][0].sound->unflag = LoadSound("son/unflag2.wav");
	soundArray[0] = LoadSound("son/3.wav");
	int timeOut = 99999;
// 	while (!IsSoundReady(soundArray[0]) || !IsSoundReady(grid[0][0].sound->boom) || timeOut <= 0) timeOut--; if (timeOut == 0) { printf("error soundArray not ready timed out\n"); exit(1); }
	SetSoundVolume(soundArray[0], 0.05f);
	for (int i = 1; i < MAX_SOUNDS; i++)
	{ soundArray[i] = LoadSoundAlias(soundArray[0]); SetSoundVolume(soundArray[i], 0.05f); }

	SetSoundVolume(grid[0][0].sound->boom, 0.2f);
	SetSoundVolume(grid[0][0].sound->flag, 2.0f);
	SetSoundVolume(grid[0][0].sound->success[0], 0.05f);
	SetSoundVolume(grid[0][0].sound->success[1], 0.05f);
	SetSoundVolume(grid[0][0].sound->success[2], 0.05f);
	SetSoundVolume(grid[0][0].sound->success[3], 0.05f);
	SetSoundVolume(grid[0][0].sound->success[4], 0.05f);
	SetSoundVolume(grid[0][0].sound->unflag, 0.8f);
	SetMasterVolume(1.0f);
}

void set_txt(c_square grid[NUMBER_Y][NUMBER_Y])
{
	Image atlas_number_svg = LoadImageSvg("atlas/drawing.svg", 350, 35);
	Image tile_svg = LoadImageSvg("atlas/unopened_square.svg", 70, 70);
	Image mine_2_svg = LoadImageSvg("atlas/mine2.svg", 70, 70);

	myTxt Bomb;
	Bomb.texture = LoadTexture("atlas/bomb_sprite72.png");
	Bomb.frame.x = 0; Bomb.frame.y = 0;
	Bomb.frame.width = Bomb.texture.width/72; Bomb.frame.height = Bomb.texture.height;
	Bomb.anim = false; Bomb.current_frame = 22; Bomb.scale = 0;

	myTxt Flag;
	Flag.texture = LoadTexture("atlas/flag_sprite73.png");
	Flag.frame.x = 0; Flag.frame.y = 0;
	Flag.frame.width = Flag.texture.width/73; Flag.frame.height = Flag.texture.height;
	Flag.anim = false; Flag.current_frame = 0;

	grid[0][0].sqTxt->tile_tx = LoadTextureFromImage(tile_svg);
	grid[0][0].sqTxt->mine1_txt = LoadTextureFromImage(mine_2_svg);
	grid[0][0].sqTxt->atlas = LoadTextureFromImage(atlas_number_svg);

	grid[0][0].sqTxt->cats[0] = LoadTexture("atlas/wrysmilecat_sprite73.png");
	grid[0][0].sqTxt->cats[1] = LoadTexture("atlas/Catweary63.png");
	grid[0][0].sqTxt->cats[2] = LoadTexture("atlas/tearsofjoyCat49.png");
//  	grid[0][0].sqTxt->cats[3] = LoadTexture("atlas/crycat_sprite93-ezgif.com-resize.png");
  	grid[0][0].sqTxt->cats[3] = LoadTexture("atlas/crycat_sprite93.png");
	grid[0][0].sqTxt->cats[4] = LoadTexture("atlas/normalcat_sprite73.png");
	grid[0][0].sqTxt->cats[5] = LoadTexture("atlas/CatSprite.png");
	grid[0][0].sqTxt->cats[6] = LoadTexture("atlas/heartEyesCat_sprite72.png");
	grid[0][0].sqTxt->cats[7] = LoadTexture("atlas/heartkisscat_sprite73.png");

	grid[0][0].sqTxt->cat_frame.y = 0;
	grid[0][0].sqTxt->cat_frame.x = 0;
	grid[0][0].sqTxt->cat_frame.height = grid[0][0].sqTxt->cats[g_mood].height;
	grid[0][0].sqTxt->cat_frame.width = grid[0][0].sqTxt->cats[g_mood].width/MAX_SPRITE[g_mood];

	//TODO: remove 35 -> magic number = bad
	grid[0][0].sqTxt->number_svg.x = 0; grid[0][0].sqTxt->number_svg.y = 0;
	grid[0][0].sqTxt->number_svg.width = 35; grid[0][0].sqTxt->number_svg.height = 35;

// 	int timeOut = 999999; while (!IsTextureReady(grid[0][0].sqTxt->atlas) || !IsTextureReady(grid[0][0].sqTxt->cats[0]) || !IsTextureReady(grid[0][0].sqTxt->tile_tx) || !IsTextureReady(grid[0][0].sqTxt->mine_mark_txt) || !IsTextureReady(grid[0][0].sqTxt->mine2_txt) || !IsTextureReady(grid[0][0].sqTxt->mine1_txt)) timeOut--; if (timeOut == 0) { printf("error audiodevice not ready timed out\n"); exit(1); }
	UnloadImage(mine_2_svg); UnloadImage(tile_svg); UnloadImage(atlas_number_svg);

 	grid[0][0].sqTxt->myFlag = Flag;
 	grid[0][0].sqTxt->myBomb = Bomb;
}

void print_grid(c_square grid[NUMBER_Y][NUMBER_X])
{
	for (int i = 0; i < NUMBER_Y; i++)
	{
		for(int j = 0; j < NUMBER_X; j++)
		{
			if (grid[i][j].anim)
				printf("grid[%d][%d].anim = %d\n", i, j, grid[i][j].anim);
		}
	}
}
//this function is a joke, really
void cleaner(void *ptr)
{
	free(ptr);
	CloseAudioDevice();
	CloseWindow();
}

/*
Vector2 is_mouse_rect_click(c_square (grid)[NUMBER_Y][NUMBER_X],
		Vector2 mousePosition)
{
    int col = (int)(mousePosition.x / (GRID_WIDTH / (float)NUMBER_X));
    int row = (int)(mousePosition.y / (GRID_HEIGHT/ (float)NUMBER_Y));

	if (is_inBounds(grid, mousePosition, col, row))
		(grid)[row][col].clicked = true;
	return (Vector2){row, col};
}
*/
