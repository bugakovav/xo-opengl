#include "headers\stdafx.h"
#include "headers\vars.h"

#include "headers\glut.h"
#include "headers\bot.h"

#define checksize if (cols < 5 and rows < 5) return -1;

u_int max_height = (u_int) 1080;
u_int max_width = (u_int) 1920;

u_int width, height;

u_int scale = 70, cols, rows;

bool player = 0, win = 0;

int game_mode = -1;

cell** field = NULL;

cell* pots = NULL;

u_int count_pots = 0, count_moves = 0;

u_int bot_last_y, bot_last_x;

u_int player_last_y, player_last_x;

u_int win_x[5];

u_int win_y[5];

bool first_bot_move_t = 0;

static int menu_id;
static int submenu_id;
static int window_id;
static int value;

bool init();
void reset();

void menu_func0(int value)
{
	if (value == 0)
	{
		game_mode = 0;
		reset();
	}
	else if (value == 1)
	{
		game_mode = 1;
		reset();
	}

	glutPostRedisplay();
}

void menu_func1(int value)
{
	if (value == 0)
	{
		glutDestroyWindow(window_id);
		exit(0);
	}
	else if(value == 1)
	{
		reset();
	}

	glutPostRedisplay();
}

void create_menu(void)
{
	submenu_id = glutCreateMenu(menu_func0);
	glutAddMenuEntry("Player vs bot", 0);
	glutAddMenuEntry("Player vs player", 1);
	

	menu_id = glutCreateMenu(menu_func1);
	glutAddMenuEntry("Reset", 1);
	glutAddSubMenu("Gamemode", submenu_id);
	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reset()
{
	win = 0;

	for (int i = 0; i < rows; i++)
		free(field[i]);

	free(field);

	free(pots);

	first_bot_move_t = 0;

	count_moves = 0;

	count_pots = 0;

	pots = NULL;

	field = NULL;

	player = 0;

	rows = 5;

	cols = 5;

	width = cols * scale;

	height = rows * scale;

	init();
}

bool init()
{
	if (pots != NULL or field != NULL)
		return false;

	pots = (cell*)malloc(sizeof(cell));

	field = (cell**)malloc(sizeof(cell*) * rows);

	for (u_int i = 0; i < rows; i++)
		field[i] = (cell*)malloc(sizeof(cell) * cols + 1);

	for (u_int i = 0; i < rows; i++)
	{
		for (u_int j = 0; j < cols; j++)
		{
			field[i][j].x = i;
			field[i][j].y = j;
			field[i][j].value = -1;
			field[i][j].pot = -100;
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cols = 5;
		rows = 5;
	}
	else
	{
		cols = atoi(argv[1]);
		rows = atoi(argv[2]);
	}

	checksize

	width = cols * scale;
	height = rows * scale;

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	game_mode = 0;

	if (!init())
	{
		printf("Incorrect init\n");
		return -1;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);

	window_id = glutCreateWindow("..");

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	create_menu();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse_pressed);
	glutTimerFunc(100, timer, 0);

	glutMainLoop();
}


