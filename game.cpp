#include<bits/stdc++.h>
using namespace std;

#include<stdio.h>
#include<easyx.h>
#include<math.h>
#define Bullet_Num 15
#define Balloon_Num 15

struct Balloon    //ÆøÇò
{
	int x;
	int y;
	int falg;
	COLORREF color;
}ball[Balloon_Num];


struct Bullet
{
	double x;
	double y;
	double vx;
	double vy;
	bool flag;
	COLORREF color;
}bull[Bullet_Num];

struct Battery
{
	int x;
	int y;
	int endx;
	int endy;
	int r;
	int len;
	double radian;

	int speed;
}bat;

void createBullet();

void init()
{
	bat.x = getwidth() / 2;
	bat.y = getheight() - 10;
	bat.r = 60;
	bat.len = 90;
	bat.endx = bat.x;
	bat.endy = bat.y - bat.len;
	bat.speed = 10;

	for (size_t i = 0; i < Balloon_Num; i++)
	{
		ball[i].x = rand() % (getwidth() - 30);
		ball[i].y = rand() % getheight();
		ball[i].falg = true;
		ball[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}

void draw()
{
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	for (size_t i = 0; i < Balloon_Num; i++)
	{
		if (!ball[i].falg)
			continue;
		setfillcolor(ball[i].color);
		solidellipse(ball[i].x, ball[i].y, ball[i].x + 30, ball[i].y + 60);
		arc(ball[i].x + 5, ball[i].y + 5, ball[i].x + 30 - 5, ball[i].y + 60 - 5, 0, 1.2);
		arc(ball[i].x , ball[i].y + 60, ball[i].x + 20, ball[i].y + 60 +20, 0, 1.2);
	}

	setlinestyle(PS_SOLID,3);
	setlinecolor(BLACK);
	setfillcolor(BLACK);

	circle(bat.x, bat.y, bat.r);
	solidcircle(bat.x, bat.y, 5);
	line(bat.x, bat.y, bat.endx, bat.endy);

	for (size_t i = 0; i < Bullet_Num; i++)
	{
		if (bull[i].flag)
		{
			setfillcolor(bull[i].color);
			solidcircle(bull[i].x, bull[i].y, 5);
		}
	}
}

void mouseEvent()
{
	static ExMessage msg;

	if (peekmessage(&msg,EM_MOUSE))
	{
		bat.radian = atan2(bat.y - msg.y, msg.x - bat.x);
		bat.endx = bat.x + cos(bat.radian) * bat.len;
		bat.endy = bat.y - sin(bat.radian) * bat.len;

		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
			createBullet();
			break;
		case WM_RBUTTONDOWN:
			printf("WM_RBUTTONDOWN\n");
			break;
		case WM_MOUSEWHEEL:
			printf("WM_MOUSEWHEEL\n");
			break;
		}
	}
}

void createBullet()
{
	for (size_t i = 0; i < Bullet_Num; i++)
	{
		if (!bull[i].flag)
		{
			bull[i].flag = true;
			bull[i].x = bat.endx;
			bull[i].y = bat.endy;
			bull[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			bull[i].vx = bat.speed * cos(bat.radian);
			bull[i].vy = bat.speed * sin(bat.radian);
			break;
		}
	}
}


void moveBullet()
{
	for (size_t i = 0; i < Bullet_Num; i++)
	{
		if (bull[i].flag)
		{
			bull[i].x += bull[i].vx;
			bull[i].y -= bull[i].vy;
			if (bull[i].x < 0 || bull[i].x >= getwidth() || bull[i].y < 0 || bull[i].y >= getheight())
			{
				bull[i].flag = false;
			}
		}
	}
}

void playBallon()
{
	for (size_t i = 0; i < Balloon_Num; i++)
	{
		if (!ball[i].falg)
			continue;
		for (size_t k = 0; k < Bullet_Num; k++)
		{
			if (!bull[k].flag)
				continue;
			if (bull[k].x >= ball[i].x && bull[k].x <= ball[i].x + 30 && bull[k].y >= ball[i].y && bull[k].y <= ball[i].y + 60)
			{
				bull[k].flag = false;
				ball[i].falg = false;
			}
		}
	}
}


int main()
{
	initgraph(480, 760, EW_SHOWCONSOLE);

	IMAGE img_bk;

	loadimage(&img_bk, "./resource/images/bk.jpg", getwidth(), getheight());

	init();

	BeginBatchDraw();
	while (true)
	{
		cleardevice();
		putimage(0, 0, &img_bk);
		draw();
		mouseEvent();
		moveBullet();
		playBalloon();
		FlushBatchDraw();
	}
	EndBatchDraw();

	getchar();
	return 0;
}