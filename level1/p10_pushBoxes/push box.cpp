#include <stdio.h>
#include <graphics.h>
#include <conio.h>

IMAGE background, box, redBox, wall, ground, figure, aim, page, page1;
int i, j;//循环变量
int m;//关卡箱子数
int mode = 0;//关卡
int arr[12][12];//地图数组
int arr2[12][12];//备份地图数组(只备份初始地图)
int arr3[12][12];//实时备份地图 用于撤回
void UI();//初始界面
void UI1();//关于游戏界面
void UI2();//选关界面
void createMap();//初始化地图函数
int main();//声明主函数表
void direction(int x);//控制方向函数
void locateFigure();//定位小人位置
void contralGame();//控制游戏
void judge();//判断获胜
void withdraw(int x);
void redraw(int x);
void UI()
{
	setbkcolor(RGB(126, 186, 28));
	loadimage(&page, _T("7.jpg"), 480, 640);
	putimage(0, 0, &page);
	loadimage(&page1, _T("pic\\8.jpg"), 480, 60);
	putimage(0, 519, &page1);
	RECT a{ 20,530,150,557 };
	RECT b{ 170,530,300,557 };
	RECT c{ 320,530,450,557 };
	settextcolor(RGB(233, 83, 6));
	settextstyle(30, 17, _T("楷体"));
	drawtext(_T("开始游戏"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("关于游戏"), &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("选择关卡"), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 20 && m.x <= 150 && m.y >= 530 && m.y <= 557)
			{
				mode = 1;
				createMap();
				break;
			}
			if (m.x >= 170 && m.x <= 300 && m.y >= 530 && m.y <= 557)
			{
				UI1();
				break;
			}
			if (m.x >= 320 && m.x <= 530 && m.y >= 530 && m.y <= 557)
			{
				UI2();
				break;
			}
		}
	}
}
void UI1()
{
	setbkcolor(RGB(0, 122, 204));
	settextcolor(RGB(0, 0, 0));
	cleardevice();
	RECT a{ 0,50,480,640 };
	RECT b{ 0,500,480,640 };
	settextstyle(30, 17, _T("宋体"));
	drawtext(_T("\n\n  经典的推箱子是一个来自日本的古老游戏，目的是在训练你的逻辑思考能力。在一个狭小的仓库中，要求把木箱放到指定的位置，稍不小心就会出现箱子无法移动或者通道被堵住的情况，所以需要巧妙的利用有限的空间和通道，合理安排移动的次序和位置，才能顺利的完成任务。\nW S A D 控制方向"), &a, DT_WORDBREAK);
	drawtext(_T("关于游戏"), &a, DT_CENTER | DT_WORDBREAK);
	drawtext(_T("作者：hawkssssss\n按任意键返回"), &b, DT_WORDBREAK);
	_getch();
	main();
}
void UI2()
{
	int arr4[10][10];
	int n = 1;
	int s = 0;
	TCHAR Ls[10];
	setbkcolor(RGB(233, 233, 233));
	settextcolor(RGB(233, 83, 6));
	cleardevice();
	RECT b{ 0,500,480,640 };
	settextstyle(30, 17, _T("宋体"));
	setfillcolor(RGB(0, 122, 204));
	setbkcolor(RGB(0, 122, 204));
	settextcolor(RGB(0, 0, 0));
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			solidroundrect(4 * i + 40 * (i + 1) - 20, 4 * j + 40 * (j + 1) + 20, 4 * i + 40 * (i + 2) - 20, 4 * j + 40 * (j + 2) + 20, 15, 15);
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			arr4[i][j] = n;
			_stprintf(Ls, _T("%d"), n);
			RECT x{ 4 * j + 40 * (j + 1) - 20, 4 * i + 40 * (i + 1) + 20, 4 * j + 40 * (j + 2) - 20, 4 * i + 40 * (i + 2) + 20 };
			drawtext(_T(s), &x, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			n++;
		}
	}
	RECT a{ 0,0,480,60 };
	drawtext(_T("选择关卡"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("\n\n\n作者：胡军奎\n"), &b, DT_WORDBREAK);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (m.x - 20 >= 44 * i && m.x - 20 <= 40 * (i + 1) + 4 * i)
					{
						if (m.y - 60 >= 44 * j && m.y - 60 <= 40 * (j + 1) + 4 * j)
						{
							mode = arr4[j][i];
							s = 1;
							break;
						}
					}
				}
			}
			break;
		}
		if (s == 1)
			break;
	}
	createMap();
}
void redraw(int x)
{
	if (x == 1)
	{
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 12; j++)
			{
				if (arr[i][j] == 0)
					putimage(40 * j, 40 * i + 80, &background);     //这个就是重绘地图  下面 X=2时是解决目标位置会消失的情况的
				if (arr[i][j] == 1)
					putimage(40 * j, 40 * i + 80, &wall);
				if (arr[i][j] == 2)
					putimage(40 * j, 40 * i + 80, &ground);
				if (arr[i][j] == 3)
					putimage(40 * j, 40 * i + 80, &aim);
				if (arr[i][j] == 4)
					putimage(40 * j, 40 * i + 80, &box);
				if (arr[i][j] == 5)
					putimage(40 * j, 40 * i + 80, &figure);
				if (arr[i][j] == 6)
					putimage(40 * j, 40 * i + 80, &redBox);
			}
		}
	}
	if (x == 2)
	{							//在绘制地图时用arr2 数组备份了地图 
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 12; j++)
			{			//先找到目标绘位置的坐标 和红箱子的坐标 
						//（开局可能直接产生红箱子 与目标位置重合，因为地图数组记录的红箱子位置也是一个目标位置，所以要加上红箱子）
				if ((arr2[i][j] == 3 || arr2[i][j] == 6) && arr[i][j] != 6 && arr[i][j] != 5)
				{					//但是原地图数组还不能是红箱子和小人 不然会被目标位置覆盖（因为目的是把被空地取代的目标位置找回）
					arr[i][j] = 3;    //找到之后直接转换为目标位置         
					putimage(40 * j, 40 * i + 80, &aim);   //目标位置贴图       
				}
			}
		}
	}
}
void createMap()
{
	setbkcolor(RGB(233, 233, 233));
	cleardevice();
	if (mode == 1)//关卡1
	{
		m = 5;//此关箱子的个数
		int arr1[12][12] =//初始化地图数组
		{ { 0 },{ 0 },
		{ 0,0,0,0,1,1,1,1,1,1,0,0 },
		{ 0,0,1,1,1,2,2,2,2,1,0,0 },
		{ 0,1,1,3,2,4,1,1,2,1,1,0 },
		{ 0,1,3,3,4,2,4,2,2,5,1,0 },
		{ 0,1,3,3,2,4,2,4,2,1,1,0 },
		{ 0,1,1,1,1,1,1,2,2,1,0,0 },
		{ 0,0,0,0,0,0,1,1,1,1,0,0 },
		{ 0 },{ 0 },{ 0 } };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];//把地图数组复制给全局数组
				arr2[i][j] = arr1[i][j];//把地图数组复制给全局备份数组
				arr3[i][j] = arr1[i][j];
			}							//其他地图同理
	}
	if (mode == 2)
	{
		m = 3;
		int arr1[12][12] =
		{ { 0 },
		{ 0,1,1,1,1,1,0,0,0,0,0,0 },
		{ 0,1,2,2,2,1,0,0,0,0,0,0 },
		{ 0,1,2,4,2,1,0,1,1,1,0,0 },
		{ 0,1,2,4,5,1,0,1,3,1,0,0 },
		{ 0,1,1,1,4,1,1,1,3,1,0,0 },
		{ 0,0,1,1,2,2,2,2,3,1,0,0 },
		{ 0,0,1,2,2,2,1,2,2,1,0,0 },
		{ 0,0,1,2,2,2,1,1,1,1,0,0 },
		{ 0,0,1,1,1,1,1,0,0,0,0,0 },
		{ 0 },{ 0 } };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 3)
	{
		m = 4;
		int arr1[12][12] =
		{ { 0 },{ 0 },
		{ 0,0,1,1,1,1,1,1,1,0,0,0 },
		{ 0,0,1,2,2,2,2,2,1,1,1,0 },
		{ 0,1,1,4,1,1,1,2,2,2,1,0 },
		{ 0,1,2,5,2,4,2,2,4,2,1,0 },
		{ 0,1,2,3,3,1,2,4,2,1,1,0 },
		{ 0,1,1,3,3,1,2,2,2,1,0,0 },
		{ 0,0,1,1,1,1,1,1,1,1,0,0 },
		{ 0 },{ 0 },{ 0 } };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 4)
	{
		m = 5;
		int arr1[12][12] =
		{ { 0 },{ 0 },
		{ 0,0,0,0,1,1,1,1,0,0,0,0 },
		{ 0,0,0,1,1,2,2,1,0,0,0,0 },
		{ 0,0,0,1,5,4,2,1,0,0,0,0 },
		{ 0,0,0,1,1,4,2,1,1,0,0,0 },
		{ 0,0,0,1,1,2,4,2,1,0,0,0 },
		{ 0,0,0,1,3,4,2,2,1,0,0,0 },
		{ 0,0,0,1,3,3,6,3,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,0,0,0 },
		{ 0 },{ 0 } };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 5)
	{
		m = 3;
		int arr1[12][12] = {
		{ 0 },{ 0 },
		{ 0,0,0,1,1,1,1,1,0,0,0,0 },
		{ 0,0,0,1,2,5,1,1,1,0,0,0 },
		{ 0,0,0,1,2,4,2,2,1,0,0,0 },
		{ 0,0,1,1,1,2,1,2,1,1,0,0 },
		{ 0,0,1,3,1,2,1,2,2,1,0,0 },
		{ 0,0,1,3,4,2,2,1,2,1,0,0 },
		{ 0,0,1,3,2,2,2,4,2,1,0,0 },
		{ 0,0,1,1,1,1,1,1,1,1,0,0 },
		{ 0 },{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 6)
	{
		m = 5;
		int arr1[12][12] = {
		{ 0 },{ 0 },
		{ 0,0,0,1,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,2,2,1,2,5,1,0 },
		{ 0,0,0,1,2,2,2,1,4,2,1,0 },
		{ 0,0,0,1,4,2,2,4,2,2,1,0 },
		{ 0,0,0,1,2,4,1,1,2,2,1,0 },
		{ 0,1,1,1,2,4,2,1,2,1,1,0 },
		{ 0,1,3,3,3,3,3,2,2,1,0,0 },
		{ 0,1,1,1,1,1,1,1,1,1,0,0 },
		{ 0 },{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 7)
	{
		m = 5;
		int arr1[12][12] = {
		{ 0 },{ 0 },{ 0 },
		{ 0,0,0,0,1,1,1,1,1,1,0,0 },
		{ 0,0,1,1,1,2,2,2,2,1,0,0 },
		{ 0,1,1,3,2,4,1,1,2,1,1,0 },
		{ 0,1,3,3,4,2,4,2,2,5,1,0 },
		{ 0,1,3,3,2,4,2,4,2,1,1,0 },
		{ 0,1,1,1,1,1,1,2,2,1,0,0 },
		{ 0,0,0,0,0,0,1,1,1,1,0,0 },
		{ 0 },{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 8)
	{
		m = 6;
		int arr1[12][12] = {
		{ 0 },{ 0 },
		{ 0,0,1,1,1,1,1,1,1,1,1,0 },
		{ 0,0,1,2,2,1,1,2,2,2,1,0 },
		{ 0,0,1,2,2,2,4,2,2,2,1,0 },
		{ 0,0,1,4,2,1,1,1,2,4,1,0 },
		{ 0,0,1,2,1,3,3,3,1,2,1,0 },
		{ 0,1,1,2,1,3,3,3,1,2,1,1 },
		{ 0,1,2,4,2,2,4,2,2,4,2,1 },
		{ 0,1,2,2,2,2,2,1,2,2,5,1 },
		{ 0,1,1,1,1,1,1,1,1,1,1,1 },
		{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 9)
	{
		m = 5;
		int arr1[12][12] = {
		{ 0 },{ 0 },{ 0 },
		{ 0,0,0,0,1,1,1,1,1,1,0,0 },
		{ 0,0,0,0,1,2,2,2,2,1,0,0 },
		{ 0,0,1,1,1,4,4,4,2,1,0,0 },
		{ 0,0,1,5,2,4,3,3,2,1,0,0 },
		{ 0,0,1,2,4,3,3,3,1,1,0,0 },
		{ 0,0,1,1,1,1,2,2,1,0,0,0 },
		{ 0,0,0,0,0,1,1,1,1,0,0,0 },
		{ 0 },{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	if (mode == 10)
	{
		m = 4;
		int arr1[12][12] = {
		{ 0 },{ 0 },{ 0 },
		{ 0,1,1,1,1,0,0,1,1,1,1,1 },
		{ 1,1,2,2,1,0,0,1,2,2,2,1 },
		{ 1,2,4,2,1,1,1,1,4,2,2,1 },
		{ 1,2,2,4,3,3,3,3,2,4,2,1 },
		{ 1,1,2,2,2,2,1,2,5,2,1,1 },
		{ 0,1,1,1,1,1,1,1,1,1,1,0 },
		{ 0 },{ 0 },{ 0 }, };
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr[i][j] = arr1[i][j];
				arr2[i][j] = arr1[i][j];
				arr3[i][j] = arr1[i][j];
			}
	}
	loadimage(&background, _T("pic\\0.jpg"), 40, 40);
	loadimage(&wall, _T("pic\\1.jpg"), 40, 40);
	loadimage(&ground, _T("pic\\2.jpg"), 40, 40);
	loadimage(&aim, _T("pic\\3.jpg"), 40, 40);      //加载图片
	loadimage(&box, _T("pic\\4.jpg"), 40, 40);
	loadimage(&figure, _T("pic\\5.jpg"), 40, 40);
	loadimage(&redBox, _T("pic\\6.jpg"), 40, 40);
	RECT b{ 0,560,480,640 };
	RECT a{ 0,0,480,80 };
	RECT c{ 250,590,285,610 };
	TCHAR Ls[10];
	settextcolor(RGB(233, 83, 6));
	_stprintf(Ls, _T("%d"), mode);
	settextstyle(20, 13, _T("楷体"));
	drawtext(_T("WSAD控制方向   \nESC主菜单\n  空格撤回"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("当前第   关"), &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(s), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	redraw(1);//给地图贴图
	contralGame();
}
void direction(int x)
{
	if (x == 1)//当方向上时
	{
		locateFigure();	//	定位小人的坐标							1墙2空地3目标4箱子5人6红箱子
		if ((arr[i - 1][j] == 2 || arr[i - 1][j] == 3))//当小人前方是空地或者是目标位置
		{
			arr[i][j] = 2;//小人位置变为空地
			arr[i - 1][j] = 5;//小人前方位置变为小人           
		}
		if (arr[i - 1][j] == 4 && arr[i - 2][j] == 2)//当小人前方是箱子并且箱子的前方是空地
		{
			arr[i][j] = 2;     //小人和箱子同时向前移动一步   小人位置变为空地
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 4;
		}
		if (arr[i - 1][j] == 4 && arr[i - 2][j] == 3)//当小人前方是箱子 箱子前方是箱子目标位置
		{
			arr[i][j] = 2;      //小人和箱子同时向前移动一步 并且箱子变为红箱子   小人位置变为空地
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 6;
		}
		if (arr[i - 1][j] == 6 && arr[i - 2][j] == 3)//当小人前方为红箱子 红箱子前方为 箱子目标位置 
		{
			arr[i][j] = 2;      //小人和红箱子同时向前移动一步    小人位置变为空地
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 6;
		}                       //前面几种情况小人移动之后它的位置都会变为空地，如果这时小人从脚下踩的是目标位置的话
		redraw(1);				//那么就会产生一个BUG ：小人踩上目标位置再离开后  目标位置消失变为了空地
		redraw(2);				//这个函数解决这一个BUG
	}							//其他方向同理
	if (x == 2)
	{
		locateFigure();
		if ((arr[i + 1][j] == 2 || arr[i + 1][j] == 3))
		{
			arr[i][j] = 2;
			arr[i + 1][j] = 5;
		}
		if (arr[i + 1][j] == 4 && arr[i + 2][j] == 2)
		{
			arr[i][j] = 2;
			arr[i + 1][j] = 5;
			arr[i + 2][j] = 4;
		}
		if (arr[i + 1][j] == 4 && arr[i + 2][j] == 3)
		{
			arr[i][j] = 2;
			arr[i + 1][j] = 5;
			arr[i + 2][j] = 6;
		}
		if (arr[i + 1][j] == 6 && arr[i + 2][j] == 3)
		{
			arr[i][j] = 2;
			arr[i + 1][j] = 5;
			arr[i + 2][j] = 6;
		}
		redraw(1);
		redraw(2);
	}
	if (x == 3)
	{
		locateFigure();
		if ((arr[i][j - 1] == 2 || arr[i][j - 1] == 3))
		{
			arr[i][j] = 2;
			arr[i][j - 1] = 5;
		}
		if (arr[i][j - 1] == 4 && arr[i][j - 2] == 2)
		{
			arr[i][j] = 2;
			arr[i][j - 1] = 5;
			arr[i][j - 2] = 4;
		}
		if (arr[i][j - 1] == 4 && arr[i][j - 2] == 3)
		{
			arr[i][j] = 2;
			arr[i][j - 1] = 5;
			arr[i][j - 2] = 6;
		}
		if (arr[i][j - 1] == 6 && arr[i][j - 2] == 3)
		{
			arr[i][j] = 2;
			arr[i][j - 1] = 5;
			arr[i][j - 2] = 6;
		}
		redraw(1);
		redraw(2);
	}
	if (x == 4)
	{
		locateFigure();
		if ((arr[i][j + 1] == 2 || arr[i][j + 1] == 3))
		{
			arr[i][j] = 2;
			arr[i][j + 1] = 5;
		}
		if (arr[i][j + 1] == 4 && arr[i][j + 2] == 2)
		{
			arr[i][j] = 2;
			arr[i][j + 1] = 5;
			arr[i][j + 2] = 4;
		}
		if (arr[i][j + 1] == 4 && arr[i][j + 2] == 3)
		{
			arr[i][j] = 2;
			arr[i][j + 1] = 5;
			arr[i][j + 2] = 6;
		}
		if (arr[i][j + 1] == 6 && arr[i][j + 2] == 3)
		{
			arr[i][j] = 2;
			arr[i][j + 1] = 5;
			arr[i][j + 2] = 6;
		}
		redraw(1);
		redraw(2);
	}
}
void contralGame()
{
	char c = 0;
	while (1)
	{
		if (_kbhit)
			c = _getch();//获取键盘信息并存到c中
		switch (c)
		{
		case 'w':
		case 'W':
			withdraw(1);
			direction(1);
			judge();
			break;
		case 's':
		case 'S':
			withdraw(1);
			direction(2);
			judge();
			break;
		case 'a':
		case 'A':
			withdraw(1);
			direction(3);
			judge();
			break;
		case 'd':
		case 'D':
			withdraw(1);
			direction(4);
			judge();
			break;
		case ' ':
			withdraw(2);
			break;
		case 27:
			main();
			break;
		}
	}
}
void locateFigure()//定位小人的位置
{
	int flag = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (arr[i][j] == 5)
			{
				flag = 1;//找到位置后跳出双循环
				break;
			}
		}
		if (flag == 1)
			break;
	}
}
void judge()//判断过关的函数
{
	int s = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (arr[i][j] == 6)
				s++;
		}
	}
	if (s == m)//m是每关的箱子数     如果红箱子数等于地图原有的箱子数 那么进入下一关
	{
		mode++;//关卡变量
		createMap();
	}
}
void withdraw(int x)
{
	if (x == 1)
	{
		for (i = 0; i < 12; i++)
			for (j = 0; j < 12; j++)
			{
				arr3[i][j] = arr[i][j];
			}
	}
	if (x == 2)
	{
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 12; j++)
			{
				if (arr3[i][j] == 0)
					putimage(40 * j, 40 * i + 80, &background);
				if (arr3[i][j] == 1)
					putimage(40 * j, 40 * i + 80, &wall);
				if (arr3[i][j] == 2)
					putimage(40 * j, 40 * i + 80, &ground);
				if (arr3[i][j] == 3)
					putimage(40 * j, 40 * i + 80, &aim);
				if (arr3[i][j] == 4)
					putimage(40 * j, 40 * i + 80, &box);
				if (arr3[i][j] == 5)
					putimage(40 * j, 40 * i + 80, &figure);
				if (arr3[i][j] == 6)
					putimage(40 * j, 40 * i + 80, &redBox);
				arr[i][j] = arr3[i][j];
			}
		}
	}
}
int main()
{
	initgraph(480, 640);
	UI();
	_getch();
	closegraph();
}