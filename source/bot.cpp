#include "../headers/bot.h"
#include "../headers/compare.h"

void first_bot_move()
{
	field[rows / 2][cols / 2].x = cols / 2;
	field[rows / 2][cols / 2].y = rows / 2;
	field[rows / 2][cols / 2].value = player;
	bot_last_x = cols / 2;
	bot_last_y = rows / 2;

	player = !player;
	count_moves++;

	add_pot(bot_last_y, bot_last_x);
}

void bot_()
{
	find_move();
	find_enemy_move();
	choose_move();
}

void find_move()
{
	for (u_int i = 0; i < count_pots; i++)
	{
		pots[i].pot += compare_vertical(i, 1);
		pots[i].pot += compare_horizontal(i, 1);
		pots[i].pot += compare_diagonal(i, 1);
		pots[i].pot += compare_back_diagonal(i, 1);
	}
}

void find_enemy_move()
{
	for (u_int i = 0; i < count_pots; i++)
	{
		pots[i].pot += 1.1 * compare_vertical(i, 2);
		pots[i].pot += 1.1 * compare_horizontal(i, 2);
		pots[i].pot += 1.1 * compare_diagonal(i, 2);
		pots[i].pot += 1.1 * compare_back_diagonal(i, 2);
	}
}

void choose_move()
{
	sort();

	int max = pots[count_pots - 1].pot, count = 0, index = count_pots - 2;

	while (pots[index].pot == max)
	{
		count++;
		index--;
	}

	srand(time(NULL));

	int random_value = rand() % (count + 1);

	field[pots[count_pots - 1 - random_value].y][pots[count_pots - 1 - random_value].x].value = player;
	bot_last_x = pots[count_pots - 1 - random_value].x;
	bot_last_y = pots[count_pots - 1 - random_value].y;

	for (int i = 0; i < count_pots; i++)
		pots[i].pot = 0;

	rm_pot(bot_last_y, bot_last_x);
}

void sort()
{
	for (int i = 0; i < count_pots - 1; i++)
	{
		if (pots[i].pot > pots[i + 1].pot)
		{
			cell tmp = pots[i];
			pots[i] = pots[i + 1];
			pots[i + 1] = tmp;
		}
	}
}