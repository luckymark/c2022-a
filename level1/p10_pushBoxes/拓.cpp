//ջ�Ĳ�����ʵ�ֳ��ع���
/*

typedef struct
{
	char str[1000];//���֧��1000������
	int top;
} Stack;
//�ж�ջ�Ƿ�Ϊ��
int IsEmpty(Stack& S)
{
	return (S.top == -1 ? 1 : 0);
}
//��ջ
void Push(Stack& S, char ch)
{
	S.top++;
	S.str[S.top] = ch;
}
//��ջ
int Pop(Stack& S, char& x)
{
	if (IsEmpty(S) == 1)
		return 0;
	x = S.str[S.top];
	S.top--;
	return 1;
}
//������ջ�Ĳ���

//Ŀ�ĵص�����
typedef struct node
{
	int x, y;
}Date;
typedef struct
{
	Date d[10];//���ʮ��Ŀ�ĵء�
	int num;//������
}Destination;
//������Ŀ�ĵ�����Ľṹ��

Destination D;

//��Ŀ�ĵ�
void des(int a[13][13])
{
	int i, j, k = 0;
	D.num = 0;
	for (i = 0; i < 13; i++)
		for (j = 0; j < 13; j++)
			if (a[i][j] == 3)
			{
				D.num++;
				D.d[k].x = i;
				D.d[k++].y = j;
			}
}
//������Ŀ�ĵ�����


//�����ýṹ������ʵ�ֶ���ؿ�
#include <conio.h>
struct MAP
{
	int x;
	int y;
};
struct MAP map[];

//��ôʵ������
//��easyx?

//�������� 
int action(int a[13][13], Stack& S)
{
	char ch, x;
	/*�ҳ���5����8������λ��*/
	
/*
int i, j;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (a[i][j] == 5 || a[i][j] == 8)
				break;
		}
		if (a[i][j] == 5 || a[i][j] == 8)
			break;
	}

	ch = _getch();
	switch (ch)
	{
		//����ǰһ��
	case 'R':
		if (Pop(S, x) == 1)
		{
			//����һ�������� 
			if (x == 'W' || x == 'w')
			{
				if (x == 'W')
				{
					a[i + 1][j] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i - 1][j] -= 4;
					a[i + 1][j] += 5;
					a[i][j] -= 1;
				}
			}
			//����һ�������� 
			if (x == 'S' || x == 's')
			{
				if (x == 'S')
				{
					a[i - 1][j] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i + 1][j] -= 4;
					a[i - 1][j] += 5;
					a[i][j] -= 1;
				}
			}
			//����һ�������� 
			if (x == 'A' || x == 'a')
			{
				if (x == 'A')
				{
					a[i][j + 1] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i][j - 1] -= 4;
					a[i][j + 1] += 5;
					a[i][j] -= 1;
				}
			}
			//����һ��������
			if (x == 'D' || x == 'd')
			{

				if (x == 'D')
				{
					a[i][j - 1] += 5;
					a[i][j] -= 5;
				}
				else
				{
					a[i][j + 1] -= 4;
					a[i][j - 1] += 5;
					a[i][j] -= 1;
				}
			}
		}break;
		//�����ǳ��ع��� 

*/