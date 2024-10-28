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
	int size;   //  ����
	int dir;    //  ����
	int speed;  //  �ٶ�
	POINT coor[SNAKE_MAXNUM]; //  ����
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
	srand(GetTickCount()); // ��ȡϵͳ�������������������ĺ�����
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
	//˫�����ͼ
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	// ������
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y,5);
	}
	// ����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}


	EndBatchDraw();
}



// �ƶ���
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

//  �����ı��ߵ��ƶ�����
void keyControl()
{
	// �ж��Ƿ��а���
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
	}	// 72 80 75 77������  
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

//��Ϸ��ͣ
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


// 1����ҳ��
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