#ifndef DEMINEUR_H
#define DEMINEUR_H

#ifdef LINUX
# include <unistd.h>
#endif

# include "raylib.h"
# include <raymath.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <assert.h>

#define WINDOW_WIDTH 649
#define WINDOW_HEIGHT 749

#define GRID_HEIGHT 649
#define GRID_WIDTH 649
#define RECT_SIZE 80
#define NUMBER_X (GRID_WIDTH/RECT_SIZE)
#define NUMBER_Y (GRID_HEIGHT/RECT_SIZE)
#define TOTAL_R (NUMBER_X*NUMBER_Y)

#define MAX_SHAKE_OFFSET 10
#define MAX_ANGLE 80 * DEG2RAD

#define HOVER_DURATION_MS 50
#define FADE_OUT_DURATION_MS 500
#define THICKNESS 10

#define TOTAL_MINES (TOTAL_R/8)
#define MAX_SOUNDS 8
#define MAX_CAT_FRAMES 73

extern float ZOOM;
extern bool  SHAKE;
extern float ROTATION;
extern float OFFSET_X;
extern float OFFSET_Y;
extern float TARGET_X;
extern float TARGET_Y;
extern float SHAKE_INTENSITY;
extern Sound soundArray[MAX_SOUNDS];
extern Sound soundArrayAlias[MAX_SOUNDS];
extern int MAX_SPRITE[8];
extern int MAX_SHEET[8];
extern int frameCounter;
extern int frameSpeed;
extern int currentSound;
extern int g_current_frame;
extern int g_wait;
extern int g_mood;
extern int g_cascade;
extern int g_sprite_rows;

enum
{
	WRY = 0,
	PEUR = 1,
	CRYJOY = 2,
	CRYCAT = 3,
	NORMAL = 4,
	CAT_SPRITE = 5,
	KISSHEART = 6,
	EYESHEART = 7,
};

enum
{
	EMPTY,
	BOMB,
	NUMBER,
};

typedef struct backup
{
	int row;
	int col;
}bp;

typedef struct myTxt
{
	Texture texture;
	Rectangle frame;
	Vector2 pos;
	int x; int y;
	int w; int h;
	int current_frame;
	float scale;
	bool anim;
}myTxt;

typedef struct squareTxt
{
	Rectangle number_svg;
	Rectangle cat_frame;
	Texture cats[8];
	Texture atlas;
	Texture mine1_txt;
	Texture mine2_txt;
	Texture mine_mark_txt;
	Texture tile_tx;
	myTxt myFlag;
	myTxt myBomb;
}squareTxt;

typedef struct sfx
{
	Sound boom;
	Sound flag;
	Sound unflag;
	Sound thock;
	Sound success[5];
}sfx;

typedef struct square
{
	struct squareTxt *sqTxt;
	struct sfx *sound;
	Rectangle dimensions;
	Rectangle frame;
	int current_frame;
	int type; int bombAround;
	float scale;
	bool clicked; bool half;
	bool hovered; bool revealed;
	bool anim; bool flagged;
	bool anim2;
}c_square;

//core logic
void		set_mines(c_square grid[NUMBER_Y][NUMBER_X]);
void		cascade_click(c_square grid[NUMBER_Y][NUMBER_X], int x, int y);
void		game_over(c_square grid[NUMBER_Y][NUMBER_X]);
void		reset_game(c_square grid[NUMBER_Y][NUMBER_X]);
void		set_number_bombs(c_square grid[NUMBER_Y][NUMBER_X]);
void		cat_anim(squareTxt *gridTxt);

//drawings
void 		drawBomb(c_square grid, Texture bomb, Rectangle frame, Rectangle position, int *current_bomb, bool *anim, float *scale);
void 		drawFlagClick(c_square grid, Texture flag, Rectangle frame, Rectangle position, int *current_frame, bool *anim, float *scale);
void		drawCat(squareTxt cat_atlas, squareTxt *sqTxt);
void	 	check_squares_and_draw(c_square (sq)[NUMBER_Y][NUMBER_X]);
void		draw_grid(int thickness);
void	 	shake_window(Camera2D *camera, Camera2D backup);
void	 	is_hovered_rect(c_square (grid)[NUMBER_Y][NUMBER_X], 
				Vector2 mousePosition, bp *old);
void		key_check(c_square grid[NUMBER_Y][NUMBER_X]);
void		mouse_check(Vector2 mousePosition, c_square (ptr)[NUMBER_Y][NUMBER_X], 
				Camera2D *camera, Camera2D backup, sfx sound);

//bound check
Vector2	 	is_mouse_rect_click(c_square (grid)[NUMBER_Y][NUMBER_X],
				Vector2 mousePosition);
Vector2 	is_mouse_rect_half(c_square (grid)[NUMBER_Y][NUMBER_X],
				Vector2 mousePosition);
Vector2		get_rect_mouse(c_square (grid)[NUMBER_Y][NUMBER_X], 
				Vector2 mousePosition);
bool 		is_inBounds(c_square (grid)[NUMBER_Y][NUMBER_X], Vector2 mousePosition, 
				int col, int row);
//utils
void		init_camera(Camera2D *camera);
void		*init_squares(void);
void	 	cleaner(void *ptr);
void		debug(c_square (ptr)[NUMBER_Y][NUMBER_X]);
char	    *ft_itoa(int n);
void		print_grid(c_square grid[NUMBER_Y][NUMBER_X]);
void 		set_txt(c_square grid[NUMBER_Y][NUMBER_Y]);
void		set_sound(c_square grid[NUMBER_Y][NUMBER_Y]);

//random + failed
float		perlin(float x, float y);
double		noise(double x, double y, double z);
void		loadPermutation(char* fileName);

#endif
