#include<stdio.h>
#include"core.h"
//��Ҫ�Ƿ����ļ��㣨�ȳ���ʹ����Ԫ�飩
int sixpart[6] = { 0,0,0,0,0,0 };
int fivepart[5] = { 0,0,0,0,0 };

//����������
int calculation(int arr[15][15], Computertype computertype)
{
	int helparr[15][15] ;
	for (int a = 0; a < 15; a++)
	{
		for (int b = 0; b < 15; b++)
		{
			helparr[a][b] = arr[a][b];
		}
	}
	if (computertype == 1)
	{
		int grade = 1;
		//��������
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 10; b++)
			{
				int d = b;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[a][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//��������
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 10; b++)
			{
				int d = b;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[d++][a];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//б������
		for (int b = 0; b < 10; b++)
		{
			for (int a = b; a < 10; a++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		for (int a = 0; a < 10; a++)
		{
			for (int b = a; b < 10; b++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d++];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//�����м��ظ����˶Խ��ߣ���Ҫ��ȥ
		for (int a = 0; a < 10;a++)
		{
			for (int c = 0, d = a; c < 6; c++,d++)
			{
				sixpart[c] = helparr[d][d];
			}
			grade -= judge_sixBlack(sixpart);
			grade += judge_sixWhite(sixpart);
		}
		//��б������
		for (int b = 14; b > 4; b--)
		{
			for (int a = 14-b; a < 10; a++)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d--];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		for (int a = 0; a < 10; a++)
		{
			for (int b = 14-a; b > 4; b--)
			{
				int d = b, e = a;
				for (int c = 0; c < 6; c++)
				{
					sixpart[c] = helparr[e++][d--];
				}
				grade += judge_sixBlack(sixpart);
				grade -= judge_sixWhite(sixpart);
			}
		}
		//�����м��ظ����˶Խ��ߣ���Ҫ��ȥ
		for (int a = 0; a <10; a++)
		{
			for (int c = 0, d = a; c < 6; c++, d++)
			{
				sixpart[c] = helparr[d][14 - d];
			}
			grade -= judge_sixBlack(sixpart);
			grade += judge_sixWhite(sixpart);
		}
		//��ʼд��������������
		//��һ��
		fivepart[0] = helparr[0][4];
		fivepart[1] = helparr[1][3];
		fivepart[2] = helparr[2][2];
		fivepart[3] = helparr[3][1];
		fivepart[4] = helparr[4][0];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//�ڶ���
		fivepart[0] = helparr[10][0];
		fivepart[1] = helparr[11][1];
		fivepart[2] = helparr[12][2];
		fivepart[3] = helparr[13][3];
		fivepart[4] = helparr[14][4];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//������
		fivepart[0] = helparr[0][10];
		fivepart[1] = helparr[1][11];
		fivepart[2] = helparr[2][12];
		fivepart[3] = helparr[3][13];
		fivepart[4] = helparr[4][14];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);
		//������
		fivepart[0] = helparr[10][14];
		fivepart[1] = helparr[11][13];
		fivepart[2] = helparr[12][12];
		fivepart[3] = helparr[13][11];
		fivepart[4] = helparr[14][10];
		grade += judge_fiveBlack(fivepart);
		grade -= judge_fiveWhite(fivepart);

		return grade;
	}
	else 
	{
		//�ڰ��彻����ֱ�����ô��������
		for (int a = 0; a < 15; a++)
		{
			for (int b = 0; b < 15; b++)
			{
				if (helparr[a][b] == 0)
					continue;
				else if (helparr[a][b] == 1)
				{
					helparr[a][b] = 2;
				}
				else {
					helparr[a][b] = 1;
				}
			}
		}
		return calculation(helparr, ����);
	}
}
//����Ϊ1������Ϊ2

//��������ʼ�ж�����
int judge_sixBlack(int six[6])//�жϺ�ɫ����
{
	//�����кܶ��֣����Ŵ�Ҷ��ܿ���Ӣ�ģ��Ͳ�һһ������
	if (six[0] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1||
		six[5] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1)
	{
		return linkfive;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return livefour;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return dashfour+1;
	}
	else if (six[0] == 1 && six[1] == 0 && six[2] == 1 && six[3] == 1 && six[4] == 1 ||
		six[0] == 1 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 ||
		six[0] == 1 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1)
	{
		return dashfour;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 0)
	{
		return livethree;
	}
	else if (six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 1 && six[4] == 2||
		six[0] == 1 && six[1] == 0 && six[2] == 0 && six[3] == 1 && six[4] == 1||
		six[0] == 1 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 2||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 1 && six[5] == 0)
	{
		return sleepthree;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 0)
	{
		return livetwo;
	}
	else if (six[0] == 0 && six[1] == 1 && six[2] == 1 && six[3] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 1 && six[3] == 0||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 1 && six[4] == 2||
		six[0] == 2 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 0||
		six[0] == 0 && six[1] == 1 && six[2] == 0 && six[3] == 0 && six[4] == 1 && six[5] == 2)
	{
		return sleeptwo;
	}
	else if (six[0] == 0 && six[1] == 0 && six[2] == 1 && six[3] == 0 && six[4] == 0)
	{
		return one;
	}
	else
	{
		return 0;
	}
}

int judge_sixWhite(int six[6])//�жϰ�ɫ����
{
	for (int a = 0; a < 6; a++)
	{
		if (six[a] == 1)
		{
			six[a] = 2;
		}
		else if (six[a] == 2)
		{
			six[a] = 1;
		}
		else continue;//����ֻʣ�µ���0һ��������������������
	}
	//�ڰ���ת����ֱ������ǰ�����
	return judge_sixBlack(six);
}

//б��������������Ԫ�������������ʵ����ж�
int judge_fiveBlack(int five[5])
{
	if (five[0] == 0 && five[1] == 0 && five[2] == 0 && five[3] == 0 && five[4] == 0)
	{
		return 0;
	}
	else if (five[0]==2||five[1]==2 || five[2] == 2 || five[3] == 2 || five[4] == 2)
	{
		return deadspot;
	}
	else if (five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 1)
	{
		return linkfive;
	}
	else if (five[0] == 0 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 1 ||
		five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 0)
	{
		return dashfour;
	}
	else if (five[0] == 0 && five[1] == 1 && five[2] == 1 && five[3] == 1 && five[4] == 0||
		five[0] == 1 && five[1] == 1 && five[2] == 1 && five[3] == 0 ||
		five[1] == 0 && five[2] == 1 && five[3] == 1 && five[4] == 1)
	{
		return sleepthree;
	}
	//��ʵ���������λ���Ҿ��������������Ļ����岻�󣬺���Ͳ�д��
	else
	{
		return 0;
	}
}
//�編���ƣ�����Ƕ�׵���
int judge_fiveWhite(int five[5])
{
	for (int a = 0; a < 5; a++)
	{
		if (five[a] == 0)
		{
			continue;
		}
		else if (five[a] == 1)
		{
			five[a] = 2;
		}
		else
		{
			five[a] = 1;
		}
	}
	return judge_fiveBlack(five);
}
