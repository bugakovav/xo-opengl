#include "../headers/bot.h"
#include "../headers/compare.h"

void first_bot_move()
{
	int lrow = rows / 2;
	int lcol = cols / 2;

	field[lrow][lcol].x = lcol;
	field[lrow][lcol].y = lrow;
	field[lrow][lcol].value = player;
	bot_last_x = lcol;
	bot_last_y = lrow;

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
	//sort();

	qsort(pots, 0, count_pots - 1);

	int max = pots[count_pots - 1].pot, count = 0, index = count_pots - 2;

	while (pots[index].pot == max)
	{
		count++;
		index--;
	}

	srand(time(NULL));

	int random_value = rand() % (count + 1);

	int coord = count_pots - 1 - random_value;

	field[pots[coord].y][pots[coord].x].value = player;
	bot_last_x = pots[coord].x;
	bot_last_y = pots[coord].y;

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

void qsort(cell* numbers, int left, int right)
{
	cell change;
	cell pivot;
	int l_hold = left;
	int r_hold = right;
	int pivot2;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right].pot >= pivot.pot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++;
		}
		while ((numbers[left].pot <= pivot.pot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
		}
	}
	numbers[left] = pivot;
	pivot2 = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot2)
		qsort(numbers, left, pivot2 - 1);
	if (right > pivot2)
		qsort(numbers, pivot2 + 1, right);
}
