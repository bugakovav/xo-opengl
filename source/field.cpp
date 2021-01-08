#include "../headers/field.h"

void draw_field()
{
	glColor3f(0, 50, 100);
	glLineWidth(2);
	glBegin(GL_LINES);

	for (u_int i = scale; i < width; i += scale)
	{
		glVertex2i(i, 0);
		glVertex2i(i, height);
	}
	for (u_int i = scale; i < height; i += scale)
	{
		glVertex2i(0, i);
		glVertex2i(width, i);
	}
	glEnd();
}

void draw_cell()
{
	
	float r = (scale / 2) - 5; 

	float half_scale = (float)scale / 2;

	for (u_int i = 0; i < rows; i++)
	{
		for (u_int j = 0; j < cols; j++)
		{
			if (field[i][j].value != -1)
			{
				if (field[i][j].value == 0) {
					draw_cross(i, j);
					continue;
				}

				if (field[i][j].value == 1) {
					draw_circle((j * scale + half_scale) - 1, (i * scale + half_scale), r, 2048);
					continue;
				}

				if (field[i][j].value == 2) {
					draw_cross_win(i, j);
					continue;
				}

				if (field[i][j].value == 3) {
					draw_circle_win((j * scale + half_scale) - 1, (i * scale + half_scale), r, 2048);
					continue;
				}
			}
		}
	}
}

void draw_cross_win(u_int i, u_int j)
{
	int tmp_scale = scale - 5;

	glColor3f(255, 128, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(j * scale + 5, i * scale + 5);
	glVertex2i(j * scale + tmp_scale, i * scale + tmp_scale);
	glVertex2i(j * scale + 5, i * scale + tmp_scale);
	glVertex2i(j * scale + tmp_scale, i * scale + 5);
	glEnd();
}


void draw_circle_win(float x, float y, float r, u_int amount_segments)
{
	glColor3f(255, 128, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < amount_segments; i++)
	{
		double angle = 2.0 * 3.1415926 * i / (double)amount_segments;

		double dx = (double)r * cos(angle);
		double dy = (double)r * sin(angle);

		glVertex2d(x + dx, y + dy);
	}

	glEnd();
}

void draw_cross(u_int i, u_int j)
{
	glColor3f(0, 50, 100);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(j * scale + 5, i * scale + 5);
	glVertex2i(j * scale + scale - 5, i * scale + scale - 5);
	glVertex2i(j * scale + 5, i * scale + scale - 5);
	glVertex2i(j * scale + scale - 5, i * scale + 5);
	glEnd();
}


void draw_circle(float x, float y, float r, u_int amount_segments)
{
	glColor3f(0, 50, 100);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < amount_segments; i++)
	{
		double angle = 2.0 * 3.1415926 * i / (double)amount_segments;

		double dx = (double)r * cos(angle);
		double dy = (double)r * sin(angle);

		glVertex2d(x + dx, y + dy);
	}

	glEnd();
}

void ext_field(u_int lrow, u_int lcol)
{
	if (lcol == cols - 1 and width + scale < max_width) // right side
	{
		width = ++cols * scale;

		for (u_int i = 0; i < rows; i++)
			field[i] = (cell*)realloc(field[i], cols * sizeof(cell));

		for (u_int i = 0; i < rows; i++)
		{
			field[i][cols - 1].x = i;
			field[i][cols - 1].y = cols - 1;
			field[i][cols - 1].value = -1;
			field[i][cols - 1].pot = -100;
		}
	}

	if (lrow == rows - 1 and height + scale < max_height) // bot side
	{
		height = ++rows * scale;

		field = (cell**)realloc(field, rows * sizeof(cell*));

		field[rows - 1] = (cell*)malloc(sizeof(cell) * cols);

		for (u_int i = 0; i < cols; i++)
		{
			field[rows - 1][i].x = i;
			field[rows - 1][i].y = cols - 1;
			field[rows - 1][i].value = -1;
			field[rows - 1][i].pot = -100;
		}

	}

	if (lrow == 0 and height + scale < max_height) // top side
	{
		height = ++rows * scale;

		field = (cell**)realloc(field, rows * sizeof(cell*));

		field[rows - 1] = (cell*)malloc(sizeof(cell) * cols);

		for (u_int i = rows - 1; i > 0; i--)
		{
			for (u_int j = 0; j < cols; j++)
			{
				field[i][j].x = i;
				field[i][j].y = j;
				field[i][j].value = field[i - 1][j].value;
				field[i][j].pot = field[i - 1][j].pot;
			}
		}

		for (u_int i = 0; i < cols; i++)
		{
			field[0][i].x = 0;
			field[0][i].y = cols - 1;
			field[0][i].value = -1;
			field[0][i].pot = -100;
		}

		for (u_int i = 0; i < count_pots; i++)
			pots[i].y++;
	}

	if (lcol == 0 and width + scale < max_width) // left side
	{
		width = ++cols * scale;

		for (u_int i = 0; i < rows; i++)
			field[i] = (cell*)realloc(field[i], cols * sizeof(cell));

		for (u_int i = 0; i < rows; i++)
		{
			for (u_int j = cols - 1; j > 0; j--)
			{
				field[i][j].x = i;
				field[i][j].y = j;
				field[i][j].value = field[i][j - 1].value;
				field[i][j].pot = field[i][j - 1].pot;
			}
		}

		for (u_int i = 0; i < rows; i++)
		{
			field[i][0].x = i;
			field[i][0].y = 0;
			field[i][0].value = -1;
			field[i][0].pot = -100;
		}

		for (u_int i = 0; i < count_pots; i++)
			pots[i].x++;
	}
}
