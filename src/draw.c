#include "demineur.h"
#include "raylib.h"

static void draw_state_type(c_square sq, squareTxt *sqTxt, int *current_frame, bool *anim, float *scale);

#ifdef MAC
void	draw_grid(int thickness)
{	
	int i = 0;
    int j = 0;

    for (i = 0; i <= NUMBER_X; i++) {
        Vector2 startPos = { RECT_SIZE * i + thickness / 2, 100 };
        Vector2 endPos = { RECT_SIZE * i + thickness / 2, GRID_HEIGHT + 100 };
        DrawLineEx(startPos, endPos, thickness, DARKGRAY);
    }

    for (j = 0; j <= NUMBER_Y; j++) {
        Vector2 startPos = { 0, RECT_SIZE * j + thickness / 2 + 100 };
        Vector2 endPos = { GRID_WIDTH, RECT_SIZE * j + thickness / 2 + 100 };
        DrawLineEx(startPos, endPos, thickness, DARKGRAY);
    }
}

#else
void	draw_grid(int thickness)
{
	int i = 0; int j = thickness;
	int number_x = 0;
	int number_y = 0;

	while (number_x <= NUMBER_X)
	{
		j = 0;
		// INFO: actually "DrawLineEx" does it for you ... stupid.
		while (j < thickness)
		{
			DrawLine((RECT_SIZE*i)+j, 100, (RECT_SIZE*i)+j, GRID_HEIGHT + 100, DARKGRAY);
			j++;
		}
		i++; number_x++;
	}
	i = 0;
	j = thickness;
	while (number_y <= NUMBER_Y)
	{
		j = 0;
		while (j < thickness)
		{
			DrawLine(0, (RECT_SIZE*i)+j + 100, GRID_WIDTH, (RECT_SIZE*i)+j + 100, DARKGRAY);
			j++;
		}
		i++; number_y++;
	}
}
#endif

static	Color set_bg_color(int bombAround)
{
	Color bg;
	switch (bombAround)
	{
		case 1: bg = BEIGE; break;
		case 2: bg = DARKGREEN; break;
		case 3: bg = PURPLE; break;
		case 4: bg = DARKBLUE; break;
		case 5: bg = MAGENTA; break;
		case 6: bg = LIME; break;
		case 7: bg = BLACK; break;
		case 8: bg = GOLD; break;
	}
	return bg;
}

void check_squares_and_draw(c_square sq[NUMBER_Y][NUMBER_X])
{
	int y = 0;
	int x = 0;
	while (y < NUMBER_Y)
	{
		x = 0;
		while (x < NUMBER_X)
		{
			draw_state_type(sq[y][x], sq[0][0].sqTxt, &sq[y][x].current_frame, &sq[y][x].anim, &sq[y][x].scale);
			x++;
		}
		y++;
	}
}

static void draw_state_type(c_square sq, squareTxt *sqTxt, int *current_frame, bool *anim, float *scale)
{
	if (sq.clicked)
	{
		if (sq.type == EMPTY && sq.bombAround != 0)
		{
			Color bg = set_bg_color(sq.bombAround);
			DrawRectangle
				(sq.dimensions.x, sq.dimensions.y,
				 sq.dimensions.width, sq.dimensions.height, Fade(bg, 0.5f));
			sqTxt->number_svg.x = (sq.bombAround*sqTxt->atlas.width/10);
			DrawTextureRec(sqTxt->atlas, sqTxt->number_svg,
					(Vector2){sq.dimensions.x + 27, sq.dimensions.y + 27}, WHITE);
		}
		if (sq.type == BOMB)
		{
			DrawRectangle
				(sq.dimensions.x, sq.dimensions.y,
				 sq.dimensions.width, sq.dimensions.height, MAROON);
			DrawTexture(sqTxt->mine1_txt, sq.dimensions.x+10,
					sq.dimensions.y+20, WHITE);
			drawBomb(sq, sqTxt->myBomb.texture, sqTxt->myBomb.frame, sq.dimensions, &sqTxt->myBomb.current_frame, &sqTxt->myBomb.anim, 
					&sqTxt->myBomb.scale);
		}
	}
	else if (sq.revealed)
			DrawTexture(sqTxt->mine1_txt, sq.dimensions.x+10, sq.dimensions.y+20, WHITE);
	else if (sq.flagged)
	{
		DrawTexture(sqTxt->tile_tx, sq.dimensions.x+9, sq.dimensions.y+10, Fade(DARKGRAY, 0.8f));
		drawFlagClick(sq, sqTxt->myFlag.texture, sqTxt->myFlag.frame, sq.dimensions, current_frame, anim, scale);
		return ;
	}
	else if (sq.half)
	{
		DrawRectangleLinesEx
			((Rectangle){sq.dimensions.x + 9, sq.dimensions.y + 10, 
				 sq.dimensions.width - 10, sq.dimensions.height - 10},
				 7.0f, Fade(SKYBLUE, 0.5f));
		DrawTextureEx(sqTxt->tile_tx, (Vector2) {sq.dimensions.x+17,
				sq.dimensions.y+17},0.0f, 0.8f, LIGHTGRAY);
	}
	else if (sq.hovered)
	{
		DrawTextureEx(sqTxt->tile_tx, (Vector2) {sq.dimensions.x+13,
				sq.dimensions.y+14},0.0f, 0.9f, WHITE);
	}
	else
		DrawTexture(sqTxt->tile_tx, sq.dimensions.x+10, sq.dimensions.y+10,
				WHITE);
}

// TODO: shake oriented to where the mouse cursor is
void shake_window(Camera2D *camera, Camera2D backup)
{
	static float shakeTime = 0.0f; static float shakeIntensity = 2.4f;

	camera->offset.x = OFFSET_X; camera->offset.y = OFFSET_Y;
	camera->rotation = ROTATION;
	if (SHAKE)
 		shakeTime += GetFrameTime();
	if ((shakeTime > 1.0f || shakeIntensity <= 0.0f) && SHAKE) 
	{
		shakeIntensity = 2.4f; shakeTime = 0.0f; SHAKE = false;
	}
	if (shakeIntensity > 0.0f && SHAKE) 
	{
		camera->offset.x +=
			GetRandomValue(-MAX_SHAKE_OFFSET, MAX_SHAKE_OFFSET)*shakeIntensity;
		camera->offset.y += 
			GetRandomValue(-MAX_SHAKE_OFFSET, MAX_SHAKE_OFFSET)*shakeIntensity;
		camera->rotation += 
			GetRandomValue(-MAX_ANGLE, MAX_ANGLE)*shakeIntensity;
		shakeIntensity -= 0.1f;
	}
	/*
	   if (shakeIntensity > 0.0f && SHAKE) 
	   {
	   float noiseX = noise(100.234, 10.342, 20.091829);
	   float noiseY = noise(10.1726, 100.8472834, 17.1674);

	   camera->offset.x += noiseX * MAX_SHAKE_OFFSET * shakeIntensity;
	   camera->offset.y += noiseY * MAX_SHAKE_OFFSET * shakeIntensity;
	   shakeIntensity -= 0.1f;
	   }
	   */
}
