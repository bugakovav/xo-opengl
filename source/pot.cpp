#include "../headers/pot.h"

void add_pot(u_int row, u_int col)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((row - 1 + i >= 0 and row - 1 + i < rows) and (col - 1 + j >= 0 and col - 1 + j < cols))
			{
				if (field[row - 1 + i][col - 1 + j].value == -1 and field[row - 1 + i][col - 1 + j].pot < 0)
				{
					if (row - 1 + i != row or col - 1 + j != col)
					{
						pots[count_pots].x = col - 1 + j;
						pots[count_pots].y = row - 1 + i;
						pots[count_pots].pot = 0;
						field[row - 1 + i][col - 1 + j].pot = 0;
						count_pots++;
						pots = (cell*)realloc(pots, (count_pots + 1) * sizeof(cell));
					}
				}
			}
		}
	}
}

void rm_pot(u_int row, u_int col)
{
	int i;

	for (i = 0; i < count_pots; i++)
		if (row == pots[i].y and col == pots[i].x)
			break;

	for (i; i < count_pots - 1; i++)
		pots[i] = pots[i + 1];

	pots = (cell*)realloc(pots, count_pots-- * sizeof(cell));
}
