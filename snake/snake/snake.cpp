/*
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  //光标设置的API
#include <time.h>     //食物随机
#include <conio.h>    //按键监控
//////
//辅助宏的定义
#define MAPHEIGHT 25  //窗口的属性
#define MAPWIDTH 60
#define SNAKESIZE 50  //蛇的最大节数
//数据设计
////
//食物的结构体
struct food
{
	//如何定位坐标
	int x;
	int y;
}food;
 ///////
//蛇的结构体
struct
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;//蛇的长度
	int speed;//蛇的移动速度
}snake;

///////////////////
//全局变量
int key = 'A';//初始化移动方向
int changeFlag = 0;//蛇的变化的标记

//模块化设计
//1.地图
void drawMap();
//2.食物的差生
void createFood();
//3.按键操作
void keyDown();
//4.蛇的状态：判断是否结束游戏
int snakeStatus();
//5.辅助函数：光标移动
void gotoxy(int x, int y);


int main()
{
	drawMap();
	while (1)
	{
		
		createFood();

		Sleep(snake.speed);
		keyDown();
		if (!snakeStatus())
		{
			break;
		}
		
	}
	gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2);
	printf("GameOver");



	
	system("pause");
	return 0;
}
//1.地图
void drawMap()
{   //*：蛇身 ￥：食物
	srand((unsigned int)time(NULL));//随机函数种子
	//1.圈地
	for (int i = 0; i <= MAPHEIGHT; i++)
	{
		gotoxy(0, i);
		printf("▉");
		gotoxy(MAPWIDTH, i);
		printf("▉");
	}
	for (int i = 0; i <= MAPWIDTH; i+=2)
	{
		gotoxy(i, 0);
		printf("▉");
		gotoxy(i, MAPHEIGHT);
		printf("▉");
	}
	//2.画蛇
	snake.len = 3;
	snake.speed = 300;
	snake.x[0] = MAPWIDTH / 2;
	snake.y[0] = MAPHEIGHT / 2;
	gotoxy(snake.x[0], snake.y[0]);
	printf("*");
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("*");
	}
	//画食物
	food.x = rand() % (MAPWIDTH - 4) + 2;
	food.y = rand() % (MAPHEIGHT - 2) + 1;
	gotoxy(food.x, food.y);
	printf("￥");
}

//2.食物的差生
void createFood()
{
	if (snake.x[0] == food.x&&snake.y[0] == food.y)
	{
		srand((unsigned int)time(NULL));
		while (1)
		{
			int flag = 1;
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;
			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == food.x&&snake.y[k] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag&&food.x % 2 == 0)
			{
				break;
			}
		}
		gotoxy(food.x, food.y);
		printf("￥");
		snake.len++;
		changeFlag = 1;
		
	}
}

//3.按键操作
void keyDown()
{
	//无按键处理
	if (_kbhit())
	{
		fflush(stdin);
		key = _getch();
	}
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf(" ");
	}
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
		
	}
	switch (key)
	{
	case'w':
	case'W':
		snake.y[0]--;
		break;
	case's':
	case'S':
		snake.y[0]++;
		break;
	case'a':
	case'A':
		snake.x[0] -= 2;
		break;
	case'd':
	case'D':
		snake.x[0] += 2;
		break;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("*");
	changeFlag = 0;
	gotoxy(MAPHEIGHT + 2, 0);
}

//4.蛇的状态：判断是否结束游戏
int snakeStatus()
{
	if (snake.x[0] == 0 || snake.x[0] == MAPHEIGHT - 2 || snake.y[0] == 0 || snake.y[0] == MAPWIDTH - 2)
		return 0;
	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[k] == snake.y[0])
			return 0;
	}
}

//5.辅助函数：光标移动
void gotoxy(int x, int y)
{
	//调用win32 API去设置控制台的光标位置
	//1.找到控制台的窗口
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//2.光标的结构体
	COORD coord;
	//3.设置光标
	coord.X = x;
	coord.Y = y;
	//4.同步到控制台
	SetConsoleCursorPosition(handle, coord);
}