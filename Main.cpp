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
	float x, y;
	int vy;
}Player;

typedef struct Table_t
{
	int x, y;
}Table;

int map[SCREEN_H][SCREEN_W];
Player player = { 110,24,0 };
Table table = { player.x,26 };

void Render(void);

int main(void)
{
	int code = 0;
	int cnt = 0;
	BOOL jump_flag = FALSE;
	BOOL end_flag = FALSE;

	Render();

	SetCursorVisibility(CURSOR_INVISIBLE);

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
				player.vy = -1.0f;
			}
			break;

		case KEY_ESC:
			end_flag = TRUE;
			break;
		}

		

		if (cnt % 10 == 0)
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

			player.x -= 1.0f;	// ハードルが常に動く　　　　　
		}
		if (player.x < 0)
		{
			player.x = 119;
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
	printf("GameOver");
	code = WaitKey();

	return 0;
}

void Render(void)
{
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
	printf("Move(right : →, left : ←, jump : SPACE)");
	SetCursorPosition(1, 1);
	printf("Jumping Hurdle(!) !");
}