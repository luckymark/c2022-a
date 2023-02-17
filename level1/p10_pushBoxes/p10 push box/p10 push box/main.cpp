#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <Windows.h>



int Map[3][10][10] =
{
	{//��һ��
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, },
	{//�ڶ���
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, },
	{//������
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,3,3,4,0,0,0,0,0,1},
	{1,0,0,0,0,3,0,0,0,1},
	{1,4,0,0,0,4,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,3,0,4,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}, }
};

int level = 0;//��¼��ǰ�ؿ���Ĭ��Ϊ��0��
int maparr[10][10] = { 0 };



void initGame();//��ʼ����Ϸ

void initMap();//��ͼ���غ���

void drawMap();//���ƺ���

void runGame();//������Ϸ����

void moveInmap(int off_x, int off_y);//������ƶ�����

int endGame();//��������


int main()
{
	initGame();
L:initMap();
	while (endGame())
	{
		runGame();

	}
	if (level < 3)
	{
		level++;
		if (level != 3)
			printf("��ϲͨ�����أ��������������һ��\n");
		goto L;
	}
	printf("��Ϸʤ��\n");
	return 0;
}

void initGame()
{
	printf("\n\n\n    ������--���������ʼ");
	_getch();
}

void initMap()
{
	//���ص�ǰ�ؿ���ͼ
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			maparr[i][j] = Map[level][i][j];
		}
	}
}
void drawMap()
{
	system("cls");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (maparr[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 4:
				printf("��");
				break;
			case 2 + 4:
				printf("��");
				break;
			case 3 + 4:
				printf("��");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
}
/
void runGame()
{

	switch (_getch())
	{
	case 'w':
	case 'W':
		printf("����\n");
		moveInmap(-1, 0);
		break;
	case 's':
	case 'S':
		printf("����\n");
		moveInmap(1, 0);
		break;
	case 'a':
	case 'A':
		printf("����\n");
		moveInmap(0, -1);
		break;
	case 'd':
	case 'D':
		printf("����\n");
		moveInmap(0, 1);
		break;
	default:
		break;

	}
	drawMap();

}


void moveInmap(int off_x, int off_y)
{
	int playerPos_X = 0;
	int playerPos_Y = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (2 == maparr[i][j] || 2 + 4 == maparr[i][j])
			{
				playerPos_X = i;
				playerPos_Y = j;

			}
		}
	}


	
	if (0 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
		4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])
	{
		maparr[playerPos_X][playerPos_Y] -= 2;
		maparr[playerPos_X + off_x][playerPos_Y + off_y] += 2;
	}
	else if (3 == maparr[playerPos_X + off_x][playerPos_Y + off_y] ||
		3 + 4 == maparr[playerPos_X + off_x][playerPos_Y + off_y])
	{
		if (0 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] ||
			4 == maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2])
		{
			maparr[playerPos_X][playerPos_Y] -= 2;
			//maparr[playerPos_X + 1][playerPos_Y] += 2;
			//maparr[playerPos_X+1][playerPos_Y] -= 3;
			maparr[playerPos_X + off_x][playerPos_Y + off_y] += (2 - 3);
			maparr[playerPos_X + off_x * 2][playerPos_Y + off_y * 2] += 3;
		}
	}
}

int endGame()
{
	//����
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (3 == maparr[i][j])
			{
				return 1;
			}
		}
	}
	return 0;

}
