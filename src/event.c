#include "demineur.h"

void	mouse_check(Vector2 mousePos, c_square (ptr)[NUMBER_Y][NUMBER_X],
			Camera2D *camera, Camera2D backup, sfx sound)
{
	/*this monstruosity is a nightmare to maintain/adjust 
	 * I'll have to think of a better way ..*/

	static Vector2 firstHalf;
	static Vector2 scdHalf;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		firstHalf = is_mouse_rect_half(ptr, mousePos);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (firstHalf.x < 0.0f || firstHalf.y < 0.0f)
			return ;
		if (ptr[(int)firstHalf.x][(int)firstHalf.y].flagged)
			goto skip; //because.
		ptr[(int)firstHalf.x][(int)firstHalf.y].half = false;
		scdHalf = get_rect_mouse(ptr, mousePos);
		if (scdHalf.x < 0 || scdHalf.x >= NUMBER_X || scdHalf.y < 0 
				|| scdHalf.y >= NUMBER_Y)
			return ;
		if (scdHalf.x != firstHalf.x || scdHalf.y != firstHalf.y)
			;
		else
		{
			if (!ptr[(int)scdHalf.x][(int)scdHalf.y].clicked
					&& ptr[(int)scdHalf.x][(int)scdHalf.y].type == BOMB
					&& !ptr[(int)scdHalf.x][(int)scdHalf.y].revealed)
			{ 
				ptr[0][0].sqTxt->myBomb.anim = true;
				g_mood = PEUR;
				g_current_frame = 0;
				ptr[(int)scdHalf.x][(int)scdHalf.y].clicked = true;
				game_over(ptr);
				if (!SHAKE) 
				{ SHAKE = true; PlaySound(sound.boom); } 
			}
			else if (!ptr[(int)scdHalf.x][(int)scdHalf.y].clicked
					&& !ptr[(int)scdHalf.x][(int)scdHalf.y].revealed)
			{
				ptr[(int)scdHalf.x][(int)scdHalf.y].clicked = true;
				static int old;
				int count = 0;
				while (count == old)
					count = GetRandomValue(0, 4);
				old = count;
				PlaySound(sound.success[count]);
				cascade_click(ptr, (int)scdHalf.x,(int)scdHalf.y);
			}
		}
	}
skip:
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		firstHalf = is_mouse_rect_half(ptr, mousePos);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		if (firstHalf.x < 0.0f || firstHalf.y < 0.0f)
			return ;
		ptr[(int)firstHalf.x][(int)firstHalf.y].half = false;
		scdHalf = get_rect_mouse(ptr, mousePos);
		if (scdHalf.x < 0 || scdHalf.x >= NUMBER_X || scdHalf.y < 0 
				|| scdHalf.y >= NUMBER_Y)
			return ;
		if (scdHalf.x != firstHalf.x || scdHalf.y != firstHalf.y)
			;
		else
		{
			if (ptr[(int)scdHalf.x][(int)scdHalf.y].clicked)
				return ;
			ptr[(int)scdHalf.x][(int)scdHalf.y].flagged = !ptr[(int)scdHalf.x][(int)scdHalf.y].flagged;
			if (ptr[(int)scdHalf.x][(int)scdHalf.y].flagged)
			{
				PlaySound(sound.flag); 
				ptr[(int)scdHalf.x][(int)scdHalf.y].current_frame = 35;
				ptr[(int)scdHalf.x][(int)scdHalf.y].scale = 0.0f;
				ptr[(int)scdHalf.x][(int)scdHalf.y].anim = true;
				g_mood = WRY;
				g_current_frame = 0;
			}
			else
				PlaySound(sound.unflag); 
		}
	}
}

void	key_check(c_square grid[NUMBER_Y][NUMBER_X])
{
	int key;
	if ((key = GetKeyPressed()))
	{
		if (IsKeyDown(KEY_C))
		{
			frameSpeed += 1;
			if (frameSpeed >= 60)
				frameSpeed = 60;
			printf("framespeed= %d\n", frameSpeed);
		}
		if (IsKeyDown(KEY_V))
		{
			frameSpeed -= 1;
			if (frameSpeed <= 0)
				frameSpeed = 1;
			printf("framespeed= %d\n", frameSpeed);
		}
	}
	if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))
		&& IsKeyDown(KEY_UP))
	{
	}
	else if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT_SHIFT))
		&& IsKeyDown(KEY_DOWN))
	{
	}
	else if (IsKeyDown(KEY_R))
	{
		reset_game(grid);
		g_mood = CRYJOY; g_current_frame = 0;
	}
	else if (IsKeyPressed(KEY_I))
	{
		g_mood++;
		g_current_frame = 0;
		if (g_mood > 7)
		{
			g_mood = 0;
			g_current_frame = 0;
		}
	//	OFFSET_Y += 1; printf("TARGET_Y: %f\n", OFFSET_Y);
	}
	/*
	else if (IsKeyDown(KEY_J))
	{
		OFFSET_X -= 1; printf("TARGET_X: %f\n", OFFSET_X);
	}
	else if (IsKeyDown(KEY_K))
	{
		OFFSET_Y -= 1; printf("TARGET_Y: %f\n", OFFSET_Y);
	}
	else if (IsKeyDown(KEY_L))
	{
		OFFSET_X += 1; printf("TARGET_X: %f\n", OFFSET_X);
	}	
	else if (IsKeyDown(KEY_F))
	{
		ZOOM += 0.01f; printf("ZOOM: %f\n", ZOOM);
	}
	else if (IsKeyDown(KEY_D))
	{
		ZOOM -= 0.01f; printf("ZOOM: %f\n", ZOOM);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		ROTATION += 0.01f; printf("ROTATION: %f\n", ROTATION);
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		ROTATION -= 0.01f; printf("ROTATION: %f\n", ROTATION);
	}
	else if (IsKeyDown(KEY_UP))
		TARGET_X += 1;
	else if (IsKeyDown(KEY_DOWN))
		TARGET_X -= 1;
		*/
}
