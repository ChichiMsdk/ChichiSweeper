#include "demineur.h"
#include "raylib.h"
//this again looks garbage because I couldnt come up with a better way 
//so every animation almost will have its own function XDDDDDDDD
//I should really design stuff in advance.

void drawBomb(c_square grid, Texture bomb, Rectangle frame, Rectangle position, int *current_bomb, bool *anim, float *scale)
{
	static float enough;
	enough += GetFrameTime();
	if ((*anim) == true)
	{
		if ((*current_bomb) > 57 - 1 && enough >= 32/1000 ) { (*anim) = false; *current_bomb = 22; enough = 0; return ;}
		if (*current_bomb == 56 && enough <= 80/100)
			goto skip;
		(*current_bomb)++;
		if ((*scale) < 0.5f)
			(*scale)+= 0.1f;
skip:
		frame.x = (float)(*current_bomb)*(float)bomb.width/64;
		float newX = position.x + (RECT_SIZE - 10)/2 - 55;
		float newY = position.y + (RECT_SIZE - 10)/2 - 40;
		Rectangle destRec = {newX, newY, frame.width*(*scale), frame.height*(*scale)};
		Vector2 origin = {0,0};
		int rotation = 0;
		DrawTexturePro(bomb, frame, destRec, origin, (float)rotation, WHITE);
	}
}

void drawFlagClick(c_square grid, Texture flag, Rectangle frame, Rectangle position, int *current_flag, bool *anim, float *scale)
{
	frame.height = 256;
	frame.width = 256;
	if ((*anim) == true)
	{
		if ((*current_flag) > MAX_CAT_FRAMES - 2) { (*anim) = false; *current_flag = 0; }
		(*current_flag)++;
		if ((*scale) < 0.14f)
			(*scale)+= 0.02f;
		if (*current_flag < 64)
		{
			frame.x = (float)(*current_flag)*(float)flag.width/64;
			frame.y = 0;
		}
		else
		{
			frame.x = *current_flag*256%16384;
			frame.y = (*current_flag/64)*256;
		}
	}
	float newX = position.x + (RECT_SIZE - 10)/2 - 3;
	float newY = position.y + (RECT_SIZE - 10)/2 - 10;
	Rectangle destRec = {newX, newY, frame.width*(*scale), frame.height*(*scale)};
	Vector2 origin = {0,0};
	int rotation = 0;
	DrawTexturePro(flag, frame, destRec, origin, (float)rotation, WHITE);
}

void drawCat(squareTxt atlas, squareTxt *sqTxt)
{
	DrawTextureEx(sqTxt->tile_tx, (Vector2){WINDOW_WIDTH/2 - RECT_SIZE/2 - 5, 5}, 0.0f,
			1.3f, Fade(VIOLET, 0.9f));
 	Rectangle destRec = {(WINDOW_WIDTH/2 - RECT_SIZE/2) + 245, 250, atlas.cat_frame.width*0.4,
 		atlas.cat_frame.height*0.4};
	Vector2 origin = {(float)atlas.cat_frame.width, (float)atlas.cat_frame.height};
	int rotation = 0;
	DrawTexturePro(atlas.cats[g_mood], atlas.cat_frame, destRec, origin, (float)rotation, WHITE);
}

void cat_anim(squareTxt *gridTxt)
{
	if (frameCounter >= (60/frameSpeed))
	{
		frameCounter = 0;
		if (g_current_frame > MAX_SPRITE[g_mood] - 1) {g_current_frame = 0; g_mood = GetRandomValue(4, 6);}
		if (g_mood == PEUR && g_current_frame == 61)
		{
			g_mood = CRYCAT;
			g_current_frame = 0;
		}
		if (g_mood == CRYCAT && g_current_frame == 91)
		{
			g_mood = CRYCAT;
			g_current_frame = 0;
		}
		if (g_mood == CRYJOY && g_current_frame == 47)
		{
			g_mood = KISSHEART;
			g_current_frame = 0;
		}
		else
		{
			gridTxt->cat_frame.width = 256;
			gridTxt->cat_frame.height = 256;
			if (g_current_frame < 64)
			{
				gridTxt->cat_frame.x = (float)g_current_frame*(float)gridTxt->cats[g_mood].width/MAX_SHEET[g_mood];
				gridTxt->cat_frame.y = 0;
			}
			else
			{
				gridTxt->cat_frame.x = g_current_frame*256%16384;
				gridTxt->cat_frame.y = (g_current_frame / 64) * 256;
			}
			g_current_frame++;
		}
	}

}
