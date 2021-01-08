#include "../headers/compare.h"

/*
1. xxxxx - win - 99999
2. 0xxxx0 - 4x - 7000
3. 0xxxx - semiclosed 4x - 4000
4. xxxx0 - semiclosed 4x - 4000
5. 0xxx0 - semiopened 3x - 3000
6. 0x0xxx - 4x with gap - 2000
7. 0xx0xx - 2000
8. 0xxx0x - 2000
9. xxx0x0 - 2000
10. xx0xx0 - 2000
11. x0xxx0 - 2000
12. 0xxx - semiclosed 3x - 1500
13. xxx0 - semiclosed 3x - 1500
14. 0xx0x - 3x with gap - 800
15. 0x0xx - 800
16. xx0x0 - 800
17. x0xx0 - 800
18. 0xx0 - 2x - 200
19. xx0 - semiclosed 2x - 100
20. 0xx - semiclosed 2x - 100
*/

const char* pattern[] = {
	"22222", "022220", "02222",
	"22220", "02220", "020222",
	"022022",	"022202",	"222020",
	"220220",	"202220",	"0222",
	"2220",	"02202", "02022",
	"22020", "20220", "0220",
	"220", "022"
};

const char* bot_pattern[] = {
	"11111", "011110", "01111",
	"11110", "01110", "010111",
	"011011", "011101",	"111010",
	"110110", "101110", "0111",
	"1110", "01101", "01011",
	"11010", "10110", "0110",
	"110", "011",
};

int key[20] = {
	99999, 15000, 7000,
	7000, 3000, 2000,
	2000, 2000, 2000,
	2000, 2000, 1500,
	1500, 800, 800,
	800, 800, 200,
	100, 100
};

int compare_vertical(int index, int player)
{
	int min = pots[index].y, max = pots[index].y, i, j = 0, col = pots[index].x, k;
	char* string;
	while (min > 0 && j < 5)
	{
		min--;
		j++;
	}
	j = 0;
	while (max < rows - 1 && j < 5)
	{
		max++;
		j++;
	}
	j = 0;
	string = (char*)calloc((max - min) + 2, sizeof(char));
	if (player == 1)
	{
		for (i = min; i < max + 1; i++)
		{
			if (i != pots[index].y)
			{
				if (field[i][col].value == -1)
					string[j++] = '0';
				if (field[i][col].value == 0)
					string[j++] = '1';
				if (field[i][col].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '1';
		}
	}
	else
	{
		for (i = min; i < max + 1; i++)
		{
			if (i != pots[index].y)
			{
				if (field[i][col].value == -1)
					string[j++] = '0';
				if (field[i][col].value == 0)
					string[j++] = '1';
				if (field[i][col].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '2';
		}
	}
	string[j] = '\0';
	j = 0;
	for (k = 0; k < 20; k++)
	{
		for (i = 0; i < strlen(string) + 1; i++)
		{
			if (player == 1)
			{
				if (string[i] == bot_pattern[k][0])
					while (string[i + j] == bot_pattern[k][j])
					{
						j++;
						if (strlen(bot_pattern[k]) == j)
						{
							if (k == 0)
								return (key[k] + 50000);
							return key[k];
						}
					}
				j = 0;
			}
			else
			{
				if (string[i] == pattern[k][0])
					while (string[i + j] == pattern[k][j])
					{
						j++;
						if (strlen(pattern[k]) == j)
						{
							return key[k];
						}
					}
				j = 0;
			}
		}

	}
	free(string);
}

int compare_horizontal(int index, int player)
{
	int min = pots[index].x, max = pots[index].x, i, j = 0, row = pots[index].y, k;
	char* string;
	while (min > 0 && j < 5)
	{
		min--;
		j++;
	}
	j = 0;
	while (max < cols - 1 && j < 5)
	{
		max++;
		j++;
	}
	j = 0;
	string = (char*)calloc((max - min) + 2, sizeof(char));
	for (i = min; i < max + 1; i++)
	{
		if (player == 1)
		{
			if (i != pots[index].x)
			{
				if (field[row][i].value == -1)
					string[j++] = '0';
				if (field[row][i].value == 0)
					string[j++] = '1';
				if (field[row][i].value == 1)
					string[j++] = '2';
			}
			else
			{
				string[j++] = '1';
			}
		}
		else
		{
			if (i != pots[index].x)
			{
				if (field[row][i].value == -1)
					string[j++] = '0';
				if (field[row][i].value == 0)
					string[j++] = '1';
				if (field[row][i].value == 1)
					string[j++] = '2';
			}
			else
			{
				string[j++] = '2';
			}
		}

	}
	string[j] = '\0';
	j = 0;
	for (k = 0; k < 20; k++) 
	{
		for (i = 0; i < strlen(string) + 1; i++)
		{
			if (player == 1)
			{
				if (string[i] == bot_pattern[k][0])
					while (string[i + j] == bot_pattern[k][j])
					{
						j++;
						if (strlen(bot_pattern[k]) == j)
						{
							if (k == 0)
								return (key[k] + 50000);
							return key[k];
						}
					}
				j = 0;
			}
			else
			{
				if (string[i] == pattern[k][0])
					while (string[i + j] == pattern[k][j])
					{
						j++;
						if (strlen(pattern[k]) == j)
						{
							return key[k];
						}
					}
				j = 0;
			}
		}

	}
	free(string);
}

int compare_diagonal(int index, int player)
{
	int l, minCol = pots[index].x, minRow = pots[index].y, maxCol = pots[index].x, maxRow = pots[index].y, i, j = 0, row = pots[index].y, k, firstPart = 0, secondPart = 0;
	char* string;
	while (minCol > 0 && minRow > 0 && j < 5)
	{
		minCol--;
		minRow--;
		j++;
		firstPart = j;
	}
	j = 0;
	while (maxCol < cols - 1 && maxRow < rows - 1 && j < 5)
	{
		maxCol++;
		maxRow++;
		j++;
		secondPart = j;
	}
	j = 0;
	string = (char*)calloc((firstPart + secondPart) + 2, sizeof(char));
	for (i = minRow, k = minCol; i < maxRow + 1 && k < maxCol + 1; i++, k++)
	{
		if (player == 1)
		{
			if (i != pots[index].y || k != pots[index].x)
			{
				if (field[i][k].value == -1)
					string[j++] = '0';
				if (field[i][k].value == 0)
					string[j++] = '1';
				if (field[i][k].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '1';

		}
		else
		{
			if (i != pots[index].y || k != pots[index].x)
			{
				if (field[i][k].value == -1)
					string[j++] = '0';
				if (field[i][k].value == 0)
					string[j++] = '1';
				if (field[i][k].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '2';
		}
	}
	string[j] = '\0';
	j = 0;
	for (k = 0; k < 20; k++)
	{
		for (i = 0; i < strlen(string) + 1; i++)
		{
			if (player == 1)
			{
				if (string[i] == bot_pattern[k][0])
					while (string[i + j] == bot_pattern[k][j])
					{
						j++;
						if (strlen(bot_pattern[k]) == j)
						{
							if (k == 0)
								return (key[k] + 50000);
							return key[k];
						}
					}
				j = 0;
			}
			else
			{
				if (string[i] == pattern[k][0])
					while (string[i + j] == pattern[k][j])
					{
						j++;
						if (strlen(pattern[k]) == j)
						{
							return key[k];
						}
					}
				j = 0;
			}
		}

	}
	free(string);
}

int compare_back_diagonal(int index, int player)
{
	int minCol = pots[index].x, minRow = pots[index].y, maxCol = pots[index].x, maxRow = pots[index].y, i, j = 0, row = pots[index].y, k, firstPart = 0, secondPart = 0;
	char* string;
	while (minCol < cols - 1 && minRow > 0 && j < 5)
	{
		minCol++;
		minRow--;
		j++;
		firstPart = j;
	}
	j = 0;
	while (maxCol > 0 && maxRow < rows - 1 && j < 5)
	{
		maxCol--;
		maxRow++;
		j++;
		secondPart = j;
	}
	j = 0;
	string = (char*)calloc((firstPart + secondPart) + 2, sizeof(char));
	for (i = minRow, k = minCol; i < maxRow + 1 && k > maxCol - 1; i++, k--)
	{
		if (player == 1)
		{
			if (i != pots[index].y || k != pots[index].x)
			{
				if (field[i][k].value == -1)
					string[j++] = '0';
				if (field[i][k].value == 0)
					string[j++] = '1';
				if (field[i][k].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '1';
		}
		else
		{
			if (i != pots[index].y && k != pots[index].x)
			{
				if (field[i][k].value == -1)
					string[j++] = '0';
				if (field[i][k].value == 0)
					string[j++] = '1';
				if (field[i][k].value == 1)
					string[j++] = '2';
			}
			else
				string[j++] = '2';
		}
	}
	string[j] = '\0';
	j = 0;
	for (k = 0; k < 20; k++)
	{
		for (i = 0; i < strlen(string) + 1; i++)
		{
			if (player == 1)
			{
				if (string[i] == bot_pattern[k][0])
					while (string[i + j] == bot_pattern[k][j])
					{

						j++;
						if (strlen(bot_pattern[k]) == j)
						{
							if (k == 0)
								return (key[k] + 50000);
							return key[k];
						}
					}
				j = 0;
			}
			else
			{
				if (string[i] == pattern[k][0])
					while (string[i + j] == pattern[k][j])
					{
						j++;
						if (strlen(pattern[k]) == j)
						{
							return key[k];
						}
					}
				j = 0;
			}
		}

	}
	free(string);
}
