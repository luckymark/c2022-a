// Chess.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include "GameInit.h"
#include "AI.h"
#include "resource.h"
#include "resource2.h"
#include<stdio.h>

IMAGE board_img;

ExMessage mouse;
TCHAR s[2];

int color;
int win = 0;
int round = 0;

int main()
{
	color = 1;
	loadimage(&board_img, _T("IMAGE"), MAKEINTRESOURCE(IDB_BITMAP1));
	GameInit(board_img,&round);
	if(round){
		while (1) {
			UserMouseJ(mouse, 1, &win);
			if (win) {
				break;
			}
			tempinit();
			computerdo(mouse, 2, &win);
			if (win) {
				break;
			}
		}
	}
	else {
		while (1) {
			tempinit();
			computerdo(mouse, 2, &win);
			if (win) {
				break;
			}
			UserMouseJ(mouse, 1, &win);
			if (win) {
				break;
			}
		}
	}
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
