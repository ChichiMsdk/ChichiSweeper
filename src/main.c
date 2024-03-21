#include "demineur.h"
#include <raylib.h>

bool  SHAKE = false; float SHAKE_INTENSITY = 2.4f;
float ZOOM = 1; float ROTATION = 0; float OFFSET_X = 0; float OFFSET_Y = 0; float TARGET_X = 0; float TARGET_Y = 0;

int currentSound = 0;
int frameCounter = 0; int flagCounter = 0; int frameSpeed = 24;
int g_current_frame = 0; int g_wait = 60; int g_mood = 0;
int g_cascade = 0;
int g_sprite_rows = 1;

int MAX_SHEET[8] = {64, 63, 49, 64, 64, 64, 64, 64};
int MAX_SPRITE[8] = {73, 63, 49, 93, 73, 73, 72, 73};
Sound soundArray[MAX_SOUNDS] = { 0 };

/* This shit is a hot mess, proper and intelligible variable names, 
 * or even coherent system and use of functions or variable
 * .. but it works.*/

/* TODO: - Score 
 		 - Eyes following the mouse
 		 - Particles effect
 		 - Small smooth animation for number/flag summon
 		 - MouseCursor
		 - Fix -> Resetting the game produces conecutive hover sound

these are never gonna happen btw
*/ 		 

int	main(void)
{
#ifdef __SANITIZE_ADDRESS__
	printf("Address sanitizer enabled\n");
#else
	printf("Address sanitizer not enabled\n");
#endif

#ifndef DEBUG
	SetTraceLogLevel(LOG_ERROR);
#endif

	float deltaTime; Camera2D camera; squareTxt gridTxt; sfx sound; bp old;
	Vector2 mousePos;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ChichiMining");
	InitAudioDevice();
	Image mine_spikes = LoadImage("atlas/mine_spikes.png");
	SetWindowIcon(mine_spikes);
 	SetTargetFPS(60); 

	old.col = -1; old.row = -1;
	init_camera(&camera);
	c_square(*grid)[NUMBER_X] = init_squares();
	grid[0][0].sqTxt = &gridTxt; grid[0][0].sound = &sound;
	set_mines(grid);
	set_number_bombs(grid);
	Camera2D backup = camera;
	set_sound(grid);
	set_txt(grid);
	while (!WindowShouldClose())
	{
		frameCounter++;
		cat_anim(&gridTxt);
		mousePos = GetMousePosition();
		mousePos.y -= 100.0f;
		key_check(grid);
		mouse_check(mousePos, grid, &camera, backup, sound);
		shake_window(&camera, backup);
		is_hovered_rect(grid, mousePos, &old);

		BeginDrawing(); BeginMode2D(camera); ClearBackground(GRAY);

		check_squares_and_draw(grid);
 		draw_grid(THICKNESS);
		drawCat(gridTxt, &gridTxt);
		DrawFPS(WINDOW_WIDTH - 100, 30);

		EndMode2D(); EndDrawing();
	}

	for (int i = 0; i < 8; i++) UnloadTexture(gridTxt.cats[i]);
	UnloadTexture(gridTxt.tile_tx); UnloadTexture(gridTxt.atlas);
	UnloadTexture(gridTxt.mine2_txt);
	UnloadImage(mine_spikes); 

	UnloadSound(sound.boom); UnloadSound(sound.flag); UnloadSound(sound.unflag);
	for (int i = 0; i < 5; i++) UnloadSound(sound.success[i]);
	for (int i = 1; i < MAX_SOUNDS; i++) UnloadSoundAlias(soundArray[i]);
	UnloadSound(soundArray[0]);

	cleaner(grid);
	return (0);
}
