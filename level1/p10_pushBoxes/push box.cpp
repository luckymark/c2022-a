#include <stdio.h>
#include <graphics.h>
#include <conio.h>

IMAGE background, box, redBox, wall, ground, figure, aim, page, page1;
int i, j;//ѭ������
int m;//�ؿ�������
int mode = 0;//�ؿ�
int arr[12][12];//��ͼ����
int arr2[12][12];//���ݵ�ͼ����(ֻ���ݳ�ʼ��ͼ)
int arr3[12][12];//ʵʱ���ݵ�ͼ ���ڳ���
void UI();//��ʼ����
void UI1();//������Ϸ����
void UI2();//ѡ�ؽ���
void createMap();//��ʼ����ͼ����
int main();//������������
void direction(int x);//���Ʒ�����
void locateFigure();//��λС��λ��
void contralGame();//������Ϸ
void judge();//�жϻ�ʤ
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
	settextstyle(30, 17, _T("����"));
	drawtext(_T("��ʼ��Ϸ"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("������Ϸ"), &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("ѡ��ؿ�"), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
	settextstyle(30, 17, _T("����"));
	drawtext(_T("\n\n  �������������һ�������ձ��Ĺ�����Ϸ��Ŀ������ѵ������߼�˼����������һ����С�Ĳֿ��У�Ҫ���ľ��ŵ�ָ����λ�ã��Բ�С�ľͻ���������޷��ƶ�����ͨ������ס�������������Ҫ������������޵Ŀռ��ͨ�����������ƶ��Ĵ����λ�ã�����˳�����������\nW S A D ���Ʒ���"), &a, DT_WORDBREAK);
	drawtext(_T("������Ϸ"), &a, DT_CENTER | DT_WORDBREAK);
	drawtext(_T("���ߣ�hawkssssss\n�����������"), &b, DT_WORDBREAK);
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
	settextstyle(30, 17, _T("����"));
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
	drawtext(_T("ѡ��ؿ�"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("\n\n\n���ߣ�������\n"), &b, DT_WORDBREAK);
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
					putimage(40 * j, 40 * i + 80, &background);     //��������ػ��ͼ  ���� X=2ʱ�ǽ��Ŀ��λ�û���ʧ�������
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
	{							//�ڻ��Ƶ�ͼʱ��arr2 ���鱸���˵�ͼ 
		for (i = 0; i < 12; i++)
		{
			for (j = 0; j < 12; j++)
			{			//���ҵ�Ŀ���λ�õ����� �ͺ����ӵ����� 
						//�����ֿ���ֱ�Ӳ��������� ��Ŀ��λ���غϣ���Ϊ��ͼ�����¼�ĺ�����λ��Ҳ��һ��Ŀ��λ�ã�����Ҫ���Ϻ����ӣ�
				if ((arr2[i][j] == 3 || arr2[i][j] == 6) && arr[i][j] != 6 && arr[i][j] != 5)
				{					//����ԭ��ͼ���黹�����Ǻ����Ӻ�С�� ��Ȼ�ᱻĿ��λ�ø��ǣ���ΪĿ���ǰѱ��յ�ȡ����Ŀ��λ���һأ�
					arr[i][j] = 3;    //�ҵ�֮��ֱ��ת��ΪĿ��λ��         
					putimage(40 * j, 40 * i + 80, &aim);   //Ŀ��λ����ͼ       
				}
			}
		}
	}
}
void createMap()
{
	setbkcolor(RGB(233, 233, 233));
	cleardevice();
	if (mode == 1)//�ؿ�1
	{
		m = 5;//�˹����ӵĸ���
		int arr1[12][12] =//��ʼ����ͼ����
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
				arr[i][j] = arr1[i][j];//�ѵ�ͼ���鸴�Ƹ�ȫ������
				arr2[i][j] = arr1[i][j];//�ѵ�ͼ���鸴�Ƹ�ȫ�ֱ�������
				arr3[i][j] = arr1[i][j];
			}							//������ͼͬ��
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
	loadimage(&aim, _T("pic\\3.jpg"), 40, 40);      //����ͼƬ
	loadimage(&box, _T("pic\\4.jpg"), 40, 40);
	loadimage(&figure, _T("pic\\5.jpg"), 40, 40);
	loadimage(&redBox, _T("pic\\6.jpg"), 40, 40);
	RECT b{ 0,560,480,640 };
	RECT a{ 0,0,480,80 };
	RECT c{ 250,590,285,610 };
	TCHAR Ls[10];
	settextcolor(RGB(233, 83, 6));
	_stprintf(Ls, _T("%d"), mode);
	settextstyle(20, 13, _T("����"));
	drawtext(_T("WSAD���Ʒ���   \nESC���˵�\n  �ո񳷻�"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��ǰ��   ��"), &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(s), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	redraw(1);//����ͼ��ͼ
	contralGame();
}
void direction(int x)
{
	if (x == 1)//��������ʱ
	{
		locateFigure();	//	��λС�˵�����							1ǽ2�յ�3Ŀ��4����5��6������
		if ((arr[i - 1][j] == 2 || arr[i - 1][j] == 3))//��С��ǰ���ǿյػ�����Ŀ��λ��
		{
			arr[i][j] = 2;//С��λ�ñ�Ϊ�յ�
			arr[i - 1][j] = 5;//С��ǰ��λ�ñ�ΪС��           
		}
		if (arr[i - 1][j] == 4 && arr[i - 2][j] == 2)//��С��ǰ�������Ӳ������ӵ�ǰ���ǿյ�
		{
			arr[i][j] = 2;     //С�˺�����ͬʱ��ǰ�ƶ�һ��   С��λ�ñ�Ϊ�յ�
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 4;
		}
		if (arr[i - 1][j] == 4 && arr[i - 2][j] == 3)//��С��ǰ�������� ����ǰ��������Ŀ��λ��
		{
			arr[i][j] = 2;      //С�˺�����ͬʱ��ǰ�ƶ�һ�� �������ӱ�Ϊ������   С��λ�ñ�Ϊ�յ�
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 6;
		}
		if (arr[i - 1][j] == 6 && arr[i - 2][j] == 3)//��С��ǰ��Ϊ������ ������ǰ��Ϊ ����Ŀ��λ�� 
		{
			arr[i][j] = 2;      //С�˺ͺ�����ͬʱ��ǰ�ƶ�һ��    С��λ�ñ�Ϊ�յ�
			arr[i - 1][j] = 5;
			arr[i - 2][j] = 6;
		}                       //ǰ�漸�����С���ƶ�֮������λ�ö����Ϊ�յأ������ʱС�˴ӽ��²ȵ���Ŀ��λ�õĻ�
		redraw(1);				//��ô�ͻ����һ��BUG ��С�˲���Ŀ��λ�����뿪��  Ŀ��λ����ʧ��Ϊ�˿յ�
		redraw(2);				//������������һ��BUG
	}							//��������ͬ��
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
			c = _getch();//��ȡ������Ϣ���浽c��
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
void locateFigure()//��λС�˵�λ��
{
	int flag = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			if (arr[i][j] == 5)
			{
				flag = 1;//�ҵ�λ�ú�����˫ѭ��
				break;
			}
		}
		if (flag == 1)
			break;
	}
}
void judge()//�жϹ��صĺ���
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
	if (s == m)//m��ÿ�ص�������     ��������������ڵ�ͼԭ�е������� ��ô������һ��
	{
		mode++;//�ؿ�����
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