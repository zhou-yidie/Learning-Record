#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>



using namespace std;



#define SNAKE_MAXNUM 500

enum DIR
{
	
	RIGHT,
	UP,
	LEFT,
	DOWN,
};
struct Snake
{
	int size;   //  节数
	int dir;    //  方向
	int speed;  //  速度
	POINT coor[SNAKE_MAXNUM]; //  坐标
}snake;


struct food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;


void GameInit()
{
	initgraph(640, 480);
	srand(GetTickCount()); // 获取系统开机。到现在所经过的毫秒数
	snake.size = 100;
	snake.speed = 10;
	snake.dir;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
		cout << snake.coor[i].x << snake.coor[i].y;
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	// 绘制蛇
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y,5);
	}
	// 绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}


	EndBatchDraw();
}



// 移动蛇
void snakemove()
{
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+=snake.speed;
		if (snake.coor[0].y >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-=snake.speed;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x+=snake.speed;
		if (snake.coor[0].x >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	}
}

//  按键改变蛇的移动方向
void keyControl()
{
	// 判断是否有按键
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case ' ':
			while (1)
			{
				if (_getch() == ' ')
					return;
				break;
			}
		}
	}	// 72 80 75 77上下左  
}

void eatfood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}

//游戏暂停
//void stop()
//{
//	if (_kbhit())
//	{
//		if (_getch() == ' ')
//		{
//			while (_getch() == ' ');
//		}
//	}
//}


// 1、做页面
int main()
{
	//
	GameInit();
	while (1)
	{
		snakemove();
		GameDraw();
		keyControl();
		eatfood();
		//stop();
		Sleep(100);
	}


	return 0;
}