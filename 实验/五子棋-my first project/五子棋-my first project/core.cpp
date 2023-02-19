#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"stack.h"
#include"game.h"
#include"core.h"

Stack* pStackFirst = createStack(3);

int max(int a, int b)
{
	return a > b ? a : b;
}
int min(int a, int b)
{
	return a < b ? a : b;
}

//�������Զ�ĵ�
int JudgeEmpty(int(*p)[15],int y,int x)
{
	int helparr[19][19] = {
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//1
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//2
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//5
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//10
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},//15
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} //19
	};
	int count = 0;

	//Ϊ�˼�����̫Զ�ĵ�����׼��
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			helparr[a + 2][b + 2] = p[a][b];
		}
	}
	for (int a = y; a < 5+y; a++)
	{
		for (int b = x; b < 5+x; b++)
		{
			if (helparr[a][b] == 0 || helparr[a][b] == 3)
			{
				count++;
			}
		}
	}
	//�����Χ��Ȧ��û�����ӣ����ж�Ϊ������
	if (count >= 24)
		return 1;
	else
		return 0;
}

//����������ȼ���(����Сֵ����)
Stack* SearchFirst(int depth,int p[15][15],Node*CutLeaves)
{
	int Xhelp = 0, Yhelp = 0;
	int help = INT_MIN;
	int MAXgrade = INT_MIN;//����������ֵ
	int MINgrade = INT_MAX;//������С����ֵ
	int copyarr[15][15];//��������ֵ
	
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			copyarr[a][b] = p[a][b];
		}
	}

	switch (depth)
	{
	//������Ϊmin�㣬ż����Ϊmax��
	case 1:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//���������
					continue;
				if (JudgeEmpty(copyarr, a, b))//����̫ԶҲҪ����
					continue;
				copyarr[a][b] = 2;
				MINgrade = min(MINgrade, calculation(copyarr, ����));
				copyarr[a][b] = 0;
			}
		}
		push(pStackFirst, MINgrade);
		return pStackFirst;
	case 2:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//���������
					continue;
				if (JudgeEmpty(copyarr, a, b))//����̫ԶҲҪ����
					continue;
				copyarr[a][b] = 1;
				pStackFirst = SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				MAXgrade = max(MAXgrade, pop(pStackFirst));

				//��֦
				if (MAXgrade > CutLeaves->beta)
					goto Exit;
			}
		}
		Exit:
		push(pStackFirst, MAXgrade);
		return pStackFirst;
	case 3:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//���������
					continue;
				if (JudgeEmpty(copyarr, a, b))//����̫ԶҲҪ����
					continue;
				copyarr[a][b] = 2;
				SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				MINgrade = min(MINgrade, pop(pStackFirst));

				//��֦
				CutLeaves->beta = MINgrade;
				if (MINgrade < CutLeaves->alpha)
					goto exit;
			}
		}
		exit:
		push(pStackFirst, MINgrade);
		return pStackFirst;
	case 4:
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (copyarr[a][b] != 0)//���������
					continue;
				if (JudgeEmpty(copyarr, a, b))//����̫ԶҲҪ����
					continue;
				copyarr[a][b] = 1;
				SearchFirst(depth - 1, copyarr, CutLeaves);
				copyarr[a][b] = 0;
				help = pop(pStackFirst);
				if (help > MAXgrade)
				{
					MAXgrade = help;
					Xhelp = b;
					Yhelp = a;
				}

				//��֦
				CutLeaves->alpha = MAXgrade;
			}
		}
		push(pStackFirst, Xhelp);
		push(pStackFirst, Yhelp);  //�ȴ�������x���ٴ�������y
		return pStackFirst;
	default:
		printf("������û�дﵽ���̶ֳȣ�\a\n");
		exit(0);
	}
}

//���Ժ�����ȼ���(����Сֵ����)
Stack* SearchSecond(int depth, int(*p)[15],Node*CutLeaves)
{
	int copyarr[15][15];
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			switch (p[a][b])
			{
			case 0:
				copyarr[a][b] = 0;
				break;
			case 1:
				copyarr[a][b] = 2;
				break;
			case 2:
				copyarr[a][b] = 1;
				break;
			default:printf("SearchSecond����ת������\n\a");
				exit(0);
			}
		}
	}
	return SearchFirst(depth, copyarr, CutLeaves);//�ڰ���ת��
}

Stack* AIcomputer(int (* p)[15], Computertype computertype)
{
	Node alpha_beta = { INT_MIN,INT_MAX };
	Node* CutLeaves = &alpha_beta;
	//ǰ�˽���ͺ���㷨��ͨ��
	if (computertype == 1)            //�жϵ������֣���Һ��֣�
		return SearchFirst(4, p, CutLeaves);
	else                              //�жϵ��Ժ��֣�������֣�
		return SearchSecond(4, p, CutLeaves);
}
//��������