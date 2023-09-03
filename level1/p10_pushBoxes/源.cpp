#include<stdio.h>
#include<conio.h> 
#include<windows.h>

int map[9][11] = {
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,1,0,0,0,1,1},
	{1,1,0,0,3,0,0,0,0,1,1},
	{1,1,0,3,0,3,3,3,0,1,1},
	{1,1,0,0,0,2,0,0,0,0,1},
	{1,1,0,0,1,1,1,0,3,0,1},
	{1,0,4,4,0,4,0,0,0,0,1},
	{1,0,4,4,0,4,4,3,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1}
};                    
//原始的图表，五行六列，其中 0 代表着空白的地方； 1 代表着墙；2 代表着人；
//3 代表着箱子；4 代表着箱子的终点位置。 
//图的变化要靠自己来编写数组，通过数字来进行图的构造。
void Drawmain();
void Tuidong();
void winshu();
void startmenu();

int main()//主函数 
{
	startmenu();
	while (1)            
	{
		system("cls");//对其进行清屏 
		Drawmain();
		Tuidong();
    }
	printf("shuchu \n");
	return 0;
}
//把图形刻画出来

void Drawmain()
{
	int i, j;
	winshu();//调用输赢的函数 
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 11; j++)
		{
			//case的用法：替代？可以用图！
			switch (map[i][j])
			{
			case 0:
				printf("  "); //空白的地方
				break;
			case 1:
				printf("■"); //墙 
				break;
			case 2:
				printf("♀"); //人 
				break;
			case 3:
				printf("☆"); //箱子 
				break;
			case 4:
				printf("◎"); //终点地方 
				break;
			case 6:
				printf("♂");//人加终点位置 
				break;
			case 7:
				printf("★");//箱子加终点位置
				break;
			}
		}
		printf("\n");
	}
}

//进行小人的移动，整个移动的过程就是数组变化的过程 
void Tuidong()
{
	int count, caw = 0;//行和列 
	int i, j, tui;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++)
		{
			if (map[i][j] == 2 || map[i][j] == 6)
			{
				count = i;
				caw = j;
			}
		}
	}

	tui = _getch();
	//与getchar()有区别的是：getchar()输入一个字符后需要回车来进行下一个字符的输入，
	//比较麻烦 ，getch()则不需要回车就能连续输入多个字符。 
	switch (tui)
		//为什么不把移动和判断分开？因为必须实时操作，不然无意义。
	{
		//上
	case 'W':   //（两种均可）
	case 72:
		// 1.人的前面是空地；
		// 2.人的前面是终点位置；
		// 3.人的前面是箱子；
		// 3.1.箱子的前面是空地；
		// 3.2.箱子的前面是终点位置。
		//通过数字的加减可以代表变化
		if (map[count - 1][caw] == 0 || map[count - 1][caw] == 4)
		{
			map[count][caw] -= 2;
			map[count - 1][caw] += 2;
		}
		else if (map[count - 1][caw] == 3 || map[count - 1][caw] == 7)
		{
			if (map[count - 2][caw] == 0 || map[count - 2][caw] == 4)
			{
				map[count][caw] -= 2;
				map[count - 1][caw] -= 1;
				map[count - 2][caw] += 3;
			}
		}
		break;

		//下 
	case 'S':
	case 80://键值 
		if (map[count + 1][caw] == 0 || map[count + 1][caw] == 4)
		{
			map[count][caw] -= 2;
			map[count + 1][caw] += 2;
		}

		else if (map[count + 2][caw] == 0 || map[count + 2][caw] == 4)
		{
			if (map[count + 1][caw] == 3 || map[count + 1][caw] == 7)
			{
				map[count][caw] -= 2;
				map[count + 1][caw] -= 1;
				map[count + 2][caw] += 3;
			}
		}
		break;
		//左 
	case 'A':
	case 75:
		if (map[count][caw - 1] == 0 || map[count][caw - 1] == 4)
		{
			map[count][caw] -= 2;
			map[count][caw - 1] += 2;
		}

		else if (map[count][caw - 2] == 0 || map[count][caw - 2] == 4)
		{
			if (map[count][caw - 1] == 3 || map[count][caw - 1] == 7)
			{
				map[count][caw] -= 2;
				map[count][caw - 1] -= 1;
				map[count][caw - 2] += 3;
			}
		}
		break;
		//右 
	case 'D':
	case 77:
		if (map[count][caw + 1] == 0 || map[count][caw + 1] == 4)
		{
			map[count][caw] -= 2;
			map[count][caw + 1] += 2;
		}

		else if (map[count][caw + 2] == 0 || map[count][caw + 2] == 4)
		{
			if (map[count][caw + 1] == 3 || map[count][caw + 1] == 7)
			{
				map[count][caw] -= 2;
				map[count][caw + 1] -= 1;
				map[count][caw + 2] += 3;
			}
		}
		break;

	}
}

void winshu()
//通过判断不在目的地的箱子数
{
	int k = 0;//初始化
	int j, i;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (map[i][j] == 3)
				k++;
		}
	}
	if (k == 0)
		printf("恭喜你，你赢了！\n");
}

void startmenu()
{
	printf("   欢迎来到邵家鹏开发的推箱子小游戏 \n");
	printf("   更多新关卡正在开发主中...        \n");
	printf("   按回车开始游戏                   \n");
	getchar();
	system("cls");
}
