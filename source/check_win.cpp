#include "../headers/check_win.h"

bool check_win(u_int row, u_int col)
{
	if (check_vertical(row, col))
		return true;

	if (check_horizontal(row, col))
		return true;

	if (check_back_diagonal(row, col))
		return true;

	if (check_main_diagonal(row, col))
		return true;

	if (count_moves >= cols * rows)
		return true;

	return false;
}

bool check_vertical(u_int row, u_int col)
{
	int count = 0, i;

	for (i = row; i < rows; i++)
	{
		if (field[i][col].value == player)
		{
			win_y[count] = i;
			win_x[count] = col;

			count++;
		}
		else
		{
			i--;
			break;
		}
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	if (i == rows)
		i--;

	count = 0;

	for (i; i >= 0; i--)
	{
		if (field[i][col].value == player)
		{
			win_y[count] = i;
			win_x[count] = col;

			count++;
		}
		else
			break;
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	return 0;
}

bool check_horizontal(u_int row, u_int col)
{
	int count = 0, i;

	for (i = col; i < cols; i++)
	{
		if (field[row][i].value == player)
		{
			win_y[count] = row;
			win_x[count] = i;

			count++;
		}
		else
		{
			i--;
			break;
		}
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	if (i == cols)
		i--;

	count = 0;

	for (i; i >= 0; i--)
	{
		if (field[row][i].value == player)
		{
			win_y[count] = row;
			win_x[count] = i;

			count++;
		}
		else
			break;
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	return 0;
}

bool check_main_diagonal(u_int row, u_int col)
{
	int count = 0, i, j;

	for (i = row, j = col; i < rows and j < cols; ++i, ++j)
	{
		if (field[i][j].value == player)
		{
			win_y[count] = i;
			win_x[count] = j;

			count++;
		}
		else
		{
			i--;
			j--;
			break;
		}
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	if (i == rows or j == cols)
	{
		i--;
		j--;
	}

	count = 0;

	for (i, j; i >= 0 and j >= 0; i--, j--)
	{
		if (field[i][j].value == player)
		{
			win_y[count] = i;
			win_x[count] = j;

			count++;
		}
		else
			break;
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	return 0;
}

bool check_back_diagonal(u_int row, u_int col)
{
	int count = 0, i, j;

	for (i = row, j = col; i < rows and j >= 0; i++, j--)
	{
		//printf("rows (y) - %d cols (x) - %d\n", i, j);

		if (field[i][j].value == player)
		{
			win_y[count] = i;
			win_x[count] = j;

			count++;
		}
		else
		{
			i--;
			j++;
			break;
		}
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	if (i == rows or j == -1)
	{
		i--;
		j++;
	}

	count = 0;

	for (i, j; i >= 0 and j < cols; i--, j++)
	{
		//printf("rows (y) - %d cols (x) - %d\n", i, j);

		if (field[i][j].value == player)
		{
			win_y[count] = i;
			win_x[count] = j;

			count++;
		}
		else
			break;
	}

	if (count >= 5)
	{
		field[win_y[0]][win_x[0]].value += 2;
		field[win_y[1]][win_x[1]].value += 2;
		field[win_y[2]][win_x[2]].value += 2;
		field[win_y[3]][win_x[3]].value += 2;
		field[win_y[4]][win_x[4]].value += 2;

		return 1;
	}

	//printf("\n");

	return 0;
}
