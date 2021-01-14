#include "../headers/glut.h"

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutReshapeWindow(width, height);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (game_mode == 1 and !win)
	{
		draw_field();
		draw_cell();
	}

	if (game_mode == 0 and !win)
	{
		if (first_bot_move_t == 0)
		{
			first_bot_move();
			first_bot_move_t = 1;
		}

		draw_field();
		draw_cell();
	}

	if (game_mode == 0 or game_mode == 1 and win)
	{
		draw_field();
		draw_cell();
	}

	glutSwapBuffers();
}

void mouse_pressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and !win)
	{

		bool flag1 = 1, flag2 = 1;

		if ((player == 1 and game_mode == 0) or game_mode == 1)
		{
			u_int lrow = (u_int)y / scale;
			u_int lcol = (u_int)x / scale;

			if (lrow >= rows or lcol >= cols)
				return;

			if (field[lrow][lcol].value == -1)
				field[lrow][lcol].value = player;
			else
				return;

			win = check_win(lrow, lcol);

			if (win) return;

			player = !player;
			count_moves++;

			player_last_x = lcol;
			player_last_y = lrow;

			if (field[lrow][lcol].pot == 0)
				rm_pot(lrow, lcol);

			ext_field(lrow, lcol);

			if (lcol == 0 and game_mode == 0)
			{
				add_pot(lrow, lcol + 1);
				flag1 = 0;
			}

			if (lrow == 0 and game_mode == 0)
			{
				add_pot(lrow + 1, lcol);
				flag2 = 0;
			}

			if (flag1 and flag2)
				add_pot(lrow, lcol);

		}

		__asm
		{
			mov	byte ptr[flag1], 1
			mov	byte ptr[flag2], 1
		}

		if (game_mode == 0 and player == 0 and !win)
		{
			bot_();

			win = check_win(bot_last_y, bot_last_x);

			if (win) return;

			ext_field(bot_last_y, bot_last_x);

			if (bot_last_x == 0 and width < max_width)
			{
				add_pot(bot_last_y, bot_last_x + 1);
				flag1 = 0;
			}

			if (bot_last_y == 0 and height < max_height)
			{
				add_pot(bot_last_y + 1, bot_last_x);
				flag2 = 0;
			}

			if (flag1 and flag2)
				add_pot(bot_last_y, bot_last_x);

			player = !player;
		}
	}
}

void timer(int)
{
	display();
	glutTimerFunc(100, timer, 0);
}
