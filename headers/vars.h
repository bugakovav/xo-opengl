#pragma once

typedef unsigned int u_int;

extern u_int max_height;
extern u_int max_width;

extern u_int width, height;

extern u_int scale, cols, rows;

extern bool player, win;

extern int game_mode;

struct cell
{
	int x, y;
	int value, pot;
};

typedef struct cell cell;

extern cell** field;

extern cell* pots;

extern u_int count_pots, count_moves;

extern u_int bot_last_y, bot_last_x;

extern u_int player_last_y, player_last_x;

extern u_int win_x[];

extern u_int win_y[];

extern bool first_bot_move_t;

