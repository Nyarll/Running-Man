#include <stdio.h>
#include "Console.h"

// w : 120 h : 40	/	画面のサイズ
#define SCREEN_W 120
#define SCREEN_H 40

#define FALSE 0
#define TRUE 1

typedef short BOOL;

typedef struct Player_t
{
	int x, y;
	int vx, vy;
}Player;

typedef struct Table_t
{
	int x, y;
}Table;

int map[SCREEN_H][SCREEN_W];
Player player = { 110,24,0,0 };
Table table = { player.x,26 };

int now_score = 0;
int high_score;

void Render(void);

int main(void)
{
	int code = 0;
	int cnt = 0;
	BOOL temp = 10;
	BOOL jump_flag = FALSE;
	BOOL end_flag = FALSE;

	FILE *fp;

	fopen_s(&fp, "HighScore.txt", "r");
	fscanf_s(fp, "%d", &high_score);
	fclose(fp);

	Render();

	SetCursorVisibility(CURSOR_INVISIBLE);

	player.vx = 1;

	while (1)
	{
		//printf("test message");
		//ClearScreen();
		table.x = player.x;	// 前の座標を記憶
		table.y = player.y;	// 前の座標を記憶

		//code = WaitKey();	// キー入力を待ちつつ行動を決定
		code = GetKeyInput();

		switch (code)
		{
			/*case KEY_RIGHT:
				player.x -= 1;
				break;*/

				/*case KEY_LEFT:
					player.x += 1;
					break;*/

		case KEY_SPACE:
			if ((!jump_flag) && (player.y == 24))
			{
				jump_flag = TRUE;
				player.vy = -1;
			}
			break;

		case KEY_ESC:
			end_flag = TRUE;
			break;
		}



		if (cnt % temp == 0)
		{
			if ((jump_flag) && (player.y > 20))
			{
				player.y += player.vy;
			}
			else
			{
				player.y -= player.vy;
				jump_flag = FALSE;
			}

			player.x -= player.vx;	// ハードルが常に動く　　　　　
		}
		if (player.x < 0)
		{
			player.x = 119;
			now_score += 1;
		}
		if (player.x > 119)
		{
			player.x = 0;
		}
		if (player.y > 24)
		{
			player.y = 24;
			player.vy = 0;
		}

		switch (now_score)
		{
		case 2:
			temp = 8;
			break;
		case 4:
			temp = 6;
			break;
		case 6:
			temp = 4;
			break;
		case 8:
			temp = 2;
			break;
		case 10:
			temp = 1;
			break;
		}

		if (((int)player.x == SCREEN_W / 2) && (((int)player.y + 2) == 26))
		{
			end_flag = TRUE;
		}

		if (end_flag)
		{
			break;
		}

		Render();
		cnt++;
	}

	SetCursorPosition(SCREEN_W / 2, SCREEN_H / 2);
	if (now_score < 10)
	{
		printf("GameOver");
	}
	else
	{
		printf("Good Play !");
	}

	if (now_score >= high_score)
	{
		high_score = now_score;
	}
	code = WaitKey();
	fopen_s(&fp, "HighScore.txt", "w");
	fprintf(fp, "%d", high_score);
	fclose(fp);

	return 0;
}

void Render(void)
{
	static BOOL init_flag = FALSE;
	if (player.x != table.x)
	{
		SetCursorPosition(table.x, 26);
		printf(" ");
	}
	if (player.y != table.y)
	{
		SetCursorPosition(SCREEN_W / 2, table.y);
		printf(" ");
		SetCursorPosition(SCREEN_W / 2, table.y + 1);
		printf(" ");
		SetCursorPosition(SCREEN_W / 2, table.y + 2);
		printf(" ");
	}

	SetCursorPosition(SCREEN_W / 2, player.y);
	printf("〇");
	SetCursorPosition(SCREEN_W / 2, player.y + 1);
	printf("十");
	SetCursorPosition(SCREEN_W / 2, player.y + 2);
	printf("ミ");

	SetCursorPosition(player.x, 26);
	printf("!");

	//if (!init_flag)
	{
		SetCursorPosition(0, 27);
		for (int i = 0; i < SCREEN_W / 2; i++)
		{
			printf("■");
		}
		SetCursorPosition(0, 28);
		for (int i = 0; i < SCREEN_W / 2; i++)
		{
			printf("■");
		}
		SetCursorPosition(0, 29);
		for (int i = 0; i < SCREEN_W / 2; i++)
		{
			printf("■");
		}
		SetCursorPosition(1, 0);
		printf("Move(jump : SPACE) GameEnd : ESC");
		SetCursorPosition(1, 1);
		printf("Jumping Hurdle(!) !");

		init_flag = TRUE;
	}

	SetCursorPosition(1, 2);
	printf(" Now Score : %3d", now_score);
	SetCursorPosition(1, 3);
	printf("High Score : %3d", high_score);
}