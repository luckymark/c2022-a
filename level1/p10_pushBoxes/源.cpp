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
//ԭʼ��ͼ���������У����� 0 �����ſհ׵ĵط��� 1 ������ǽ��2 �������ˣ�
//3 ���������ӣ�4 ���������ӵ��յ�λ�á� 
//ͼ�ı仯Ҫ���Լ�����д���飬ͨ������������ͼ�Ĺ��졣
void Drawmain();
void Tuidong();
void winshu();
void startmenu();

int main()//������ 
{
	startmenu();
	while (1)            
	{
		system("cls");//����������� 
		Drawmain();
		Tuidong();
    }
	printf("shuchu \n");
	return 0;
}
//��ͼ�ο̻�����

void Drawmain()
{
	int i, j;
	winshu();//������Ӯ�ĺ��� 
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 11; j++)
		{
			//case���÷��������������ͼ��
			switch (map[i][j])
			{
			case 0:
				printf("  "); //�հ׵ĵط�
				break;
			case 1:
				printf("��"); //ǽ 
				break;
			case 2:
				printf("��"); //�� 
				break;
			case 3:
				printf("��"); //���� 
				break;
			case 4:
				printf("��"); //�յ�ط� 
				break;
			case 6:
				printf("��");//�˼��յ�λ�� 
				break;
			case 7:
				printf("��");//���Ӽ��յ�λ��
				break;
			}
		}
		printf("\n");
	}
}

//����С�˵��ƶ��������ƶ��Ĺ��̾�������仯�Ĺ��� 
void Tuidong()
{
	int count, caw = 0;//�к��� 
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
	//��getchar()��������ǣ�getchar()����һ���ַ�����Ҫ�س���������һ���ַ������룬
	//�Ƚ��鷳 ��getch()����Ҫ�س����������������ַ��� 
	switch (tui)
		//Ϊʲô�����ƶ����жϷֿ�����Ϊ����ʵʱ��������Ȼ�����塣
	{
		//��
	case 'W':   //�����־��ɣ�
	case 72:
		// 1.�˵�ǰ���ǿյأ�
		// 2.�˵�ǰ�����յ�λ�ã�
		// 3.�˵�ǰ�������ӣ�
		// 3.1.���ӵ�ǰ���ǿյأ�
		// 3.2.���ӵ�ǰ�����յ�λ�á�
		//ͨ�����ֵļӼ����Դ���仯
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

		//�� 
	case 'S':
	case 80://��ֵ 
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
		//�� 
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
		//�� 
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
//ͨ���жϲ���Ŀ�ĵص�������
{
	int k = 0;//��ʼ��
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
		printf("��ϲ�㣬��Ӯ�ˣ�\n");
}

void startmenu()
{
	printf("   ��ӭ�����ۼ���������������С��Ϸ \n");
	printf("   �����¹ؿ����ڿ�������...        \n");
	printf("   ���س���ʼ��Ϸ                   \n");
	getchar();
	system("cls");
}
