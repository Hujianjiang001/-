#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include<time.h>
IMAGE ima_background;
IMAGE ima_hero;
IMAGE ima_bee;
IMAGE ima_airplane;
IMAGE ima_bigairplane;
IMAGE ima_bullete[2];
IMAGE ima_boom;
enum my
{
	WIDTH = 400,
	HEIGHT = 700,
	BULLETE_NUM = 10,
	WIDTH1 = 66,
	HEIGHT1 = 89,
	WIDTH2 = 48,
	HEIGHT2 = 50,
	WIDTH3 = 60,
	HEIGHT3=51,
	ENEMY_NUM = 6

};
struct hero
{
	int x;
	int y;
}player;
struct enemy
{
	int x;
	int y;
	int hp;
	int type;
	bool live;

}enemy[ENEMY_NUM];
struct bullete
{
	int x;
	int y;
	bool live;
}bullete[BULLETE_NUM];
void loadimage();
void gameInit();
void gameDraw();
void playeruse(int speed);
void bulletemove(int speed);
void enemymove();
bool Timer(int ms, int id);
int main()
{
	gameInit();//游戏初始化
	loadimage();//加载图片
	//双缓冲绘图
	BeginBatchDraw();
	while (1)
	{
		gameDraw();
		playeruse(1);
		bulletemove(1);
		enemymove();
		FlushBatchDraw();//刷新界面
	}
	EndBatchDraw();//结束双缓冲绘图
}

void loadimage()
{
	loadimage(&ima_background, "HuRing/Desktop-HuRing/background.jpg");
	loadimage(&ima_hero, "C:/Users/Lenovo/Desktop/雷霆战机/hero0.png");
	loadimage(&ima_bee, "C:/Users/Lenovo/Desktop/雷霆战机/bee.png");
	loadimage(&ima_airplane, "C:/Users/Lenovo/Desktop/雷霆战机/airplane.png");
	loadimage(&ima_bigairplane, "C:/Users/Lenovo/Desktop/雷霆战机/bigairplane.png");
	loadimage(&ima_bullete[0], "C:/Users/Lenovo/Desktop/雷霆战机/bullete1.png");
	loadimage(&ima_bullete[1], "C:/Users/Lenovo/Desktop/雷霆战机/bullete2.png");
	loadimage(&ima_boom, "C:/Users/Lenovo/Desktop/雷霆战机/boom1.png");
}

void gameInit()
{
	initgraph(WIDTH, HEIGHT,SHOWCONSOLE);
	player.x = WIDTH / 2 - 49;
	player.y = HEIGHT - 139;
	for (int i = 0; i < BULLETE_NUM; i++)
	{
		bullete[i].x = player.x + 45;
		bullete[i].y = player.y;
		bullete[i].live = false;
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].x = rand() % WIDTH;
		enemy[i].y = 0;
		enemy[i].live = true;
	}
	enemy[0].hp = 3; enemy[0].type = 1;//1代表大boss
	enemy[1].hp = 2; enemy[1].type = 2;//2代表执行官
	enemy[2].hp = 2; enemy[2].type = 2;
	enemy[3].hp = 1; enemy[3].type = 3;//3代表小兵
	enemy[4].hp = 1; enemy[4].type = 3;
	enemy[5].hp = 1; enemy[5].type = 3;
}

void gameDraw()
{
	putimage(0, 0, &ima_background);
	putimage(player.x,player.y , &ima_hero);
	for (int i = 0; i < BULLETE_NUM; i++)
	{
		if (!bullete[i].live)
		{
			bullete[i].x = player.x + 45;
			bullete[i].y = player.y;
		}
		else
		{
			putimage(bullete[i].x, bullete[i].y, &ima_bullete[0]);
		}
		
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			switch (enemy[i].type)
			{
				case 1:putimage(enemy[i].x, enemy[i].y,&ima_bigairplane);
						break;
				case 2:putimage(enemy[i].x, enemy[i].y, &ima_airplane);
						break;
				case 3:putimage(enemy[i].x, enemy[i].y, &ima_bee);
						break;
			}
		}
	}
}

void playeruse(int speed)
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState ('W'))
	{
		if (player.y >= 0)
		{
			player.y-=speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y <= HEIGHT-139)
		{
			player.y+=speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x >= 0)
		{
			player.x-= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)|| GetAsyncKeyState('D'))
	{
		if (player.x <= WIDTH - 97)
		{
			player.x+= speed;
		}
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		for ( int i = 0; i < BULLETE_NUM; i++)
		{
			bullete[i].live = true;
			break;
		}
	}
}

void bulletemove(int speed)
{
	for (int i = 0; i < BULLETE_NUM; i++)
	{
		if (bullete[i].live)
		{
			bullete[i].y--;
			if (bullete[i].y <= 0)
			{
				bullete[i].live = false;
			}
		}
	}

}

void enemymove()
{
	for (int i = 0; i < ENEMY_NUM; i++ )
	{
		switch (enemy[i].type)
		{
			case 1:if (Timer(50, 1))
						enemy[i].y ++;
						break;
			case 2:if (Timer(20, 2))
						enemy[i].y++;
						break;
			case 3:if (Timer(10, 3))
						enemy[i].y++;
						break;
		}
		if (enemy[i].y >= HEIGHT)
			enemy[i].live = false;
	}
}

bool Timer(int ms, int id)
{
	static DWORD t[10];//静态变量自动初始化为0
	if (clock() - t[id] > ms)
	{
		t[id] = clock();
		return true;
	}
	return false;
}