//main.cpp
//���� �㷨 �����Ӳ��� ���ؽ��� ���˶�սҪ�Ľ������� 
#include<graphics.h>
#include<Windows.h>
#include<mmsyscom.h>//��������
#include"chessdata.h"
#include<math.h>
#include <time.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//��
IMAGE chessBlackimg;
IMAGE chessWhiteimg;
struct ChessData game;
const int map_x = 31, map_y = 37, mapchess_x = 43, mapchess_y = 42;//�������� �հ��� �������м��
//������������У�
int clickRow, clickList;

/*******************************************************************************************************/
bool kaijv()
{
	initgraph(800, 800);//�������̴���
	loadimage(0, L"wzqjm.png");
	//����
	mciSendString(L"play gfkaijv.mp3", 0, 0, 0);
	int n;
next:scanf_s("%d", &n);
	if (n == 1)return false;
	if (n == 2)return true;
	else goto next;

}

/*��Ŀ��ʼ�� �ڲ�����*/
void init() {
	initgraph(800, 796);//�������̴���
	mciSendString(L"stop gfkaijv.mp3", 0, 0, 0);
	loadimage(0, L"gfqipan.jpg");//�ַ�������
	//��������
	mciSendString(L"play kaijv.mp3", 0, 0, 0);
	loadimage(&chessBlackimg, L"hei.png", Block_size, Block_size, true);//true:�ȱ�������
	loadimage(&chessWhiteimg, L"bai.png", Block_size, Block_size, true);//true:�ȱ�������

	/*��ʼ����Ϸģ��*/
	initChessData(&game);
}

//ģ�������жϺ��� �Ƿ�ռ�� ���ڲ�������4
bool clickDIM(MOUSEMSG msg) {
	int list = (msg.x - map_x) / mapchess_x;
	int row = (msg.y - map_y) / mapchess_y;//����

	int leftTop_x = map_x + list * mapchess_x;
	int leftTop_y = map_y + row * mapchess_y;//���Ͻ�����

	int selectpot = false;//�ж��Ƿ�ѡ�õ�
	do {
		//����
		int len1 = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) + (msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len1 < Dim)
		{
			clickRow = row;
			clickList = list;
			if (game.chessMap[clickRow][clickList] == 0)//�ж��Ƿ�ռ��
			{
				selectpot = true;
			}
			break;
		}
		//����
		int len2 = sqrt((msg.x - leftTop_x + mapchess_x) * (msg.x - leftTop_x + mapchess_x) + (msg.y - leftTop_y) * (msg.y - leftTop_y));
		if (len2 < Dim)
		{
			clickRow = row;
			clickList = list + 1;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
		//����
		int len3 = sqrt((msg.x - leftTop_x) * (msg.x - leftTop_x) + (msg.y - leftTop_y + mapchess_y) * (msg.y - leftTop_y + mapchess_y));
		if (len3 < Dim)
		{
			clickRow = row + 1;
			clickList = list;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
		//����
		int len4 = sqrt((msg.x - leftTop_x + mapchess_x) * (msg.x - leftTop_x + mapchess_x) + (msg.y - leftTop_y + mapchess_y) * (msg.y - leftTop_y + mapchess_y));
		if (len4 < Dim)
		{
			clickRow = row + 1;
			clickList = list + 1;
			if (game.chessMap[clickRow][clickList] == 0)
			{
				selectpot = true;
			}
			break;
		}
	} while (0);//��ѭ������break����
	return selectpot;
}

//�ڲ�����
void chessDown(int row, int list, int i)
{
	mciSendString(L"play luozi.mp3", 0, 0, 0);
	//ͼ�ν���
	int x = map_x + clickList * mapchess_x - 0.5 * Block_size;
	int y = map_y + clickRow * mapchess_y - 0.5 * Block_size;
	if (i == -1)
	{
		putimage(x, y, &chessWhiteimg);
	}
	if (i == 1)
	{
		putimage(x, y, &chessBlackimg);
	}
}

//���ӷ��޸�ռλ ���ִ����� (�ڲ������� 
void updataGameMap(struct ChessData* data, int row, int list)
{
	if (!data)return;
	if (data->playerFlag)data->chessMap[row][list] = 1;
	else data->chessMap[row][list] = -1;
	//����
	data->playerFlag = !data->playerFlag;
}

//�������
void manGO(int n)
{
	chessDown(clickRow, clickList, n);
	updataGameMap(&game, clickRow, clickList);
}

//ai�㷨���� ��һ�� ���� ��� ���� ���� ���� ɱ�ġ� �����߷֣����ȡһ�� ���ڲ�������
void caculateScore(ChessData * data)
{
	if (!data)return;
	int personalNum = 0;//�����������Ŀ
	int botNum = 0;//ai��������Ŀ
	int emptyNum = 0;//��������հ�λ����
	//��ʼ���������� Ϊ0
	memset(data->scoreMap, 0, sizeof(data->scoreMap));
	for (int row = 0; row < Board_width; ++row)
	{
		for (int list = 0; list < Board_width; ++list)
		{
			//�հ׵����
			if (row >= 0 && list >= 0 && data->chessMap[row][list] == 0)
			{
				//�����ĸ����� ������������
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0; k < 4; ++k)
				{
					int x = directs[k][0];
					int y = directs[k][1];
					//����
					int personalNum = 0;//�����������Ŀ
					int botNum = 0;//ai��������Ŀ
					int emptyNum = 0;//��������հ�λ����
					//�Ժ�����������
					for (int i = 1; i <= 4; ++i)
					{
						if (row + i * y >= 0 && row + i * y < Board_width && list + i * x >= 0 && list + i * x <= Board_width && data->chessMap[row + i * y][list + i * x] == 0)
						{
							emptyNum++;
							break;//�����հ�λ�ã�ֹͣ�÷��������
						}
						else//���߽磬�����������壬��ֹͣ�÷��������
							break;
					}
					//�Ժ��巴������
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < Board_width && list - i * x >= 0 && list - i * x <= Board_width && data->chessMap[row - i * y][list - i * x] == 1)
						{
							personalNum++;
						}
						//�հ�λ
						else if (row - i * y >= 0 && row - i * y < Board_width && list - i * x >= 0 && list - i * x <= Board_width && data->chessMap[row - i * y][list - i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else //���߽磬��������AI����
						{
							break;
						}
					}
					if (personalNum == 1) //ɱ��
						data->scoreMap[row][list] += 10;
					else if (personalNum == 2)
					{
						if (emptyNum == 1) //����
							data->scoreMap[row][list] += 30;
						else if (emptyNum == 2) //����
							data->scoreMap[row][list] += 40;
					}
					else if (personalNum == 3)
					{
						if (emptyNum == 1) //����
							data->scoreMap[row][list] += 60;
						else if (emptyNum == 2) //����
							data->scoreMap[row][list] += 200;
					}
					else if (personalNum == 4)
						data->scoreMap[row][list] += 20000;

					//����һ�����
					emptyNum = 0;

					//�԰��������������
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y > 0 && row + i * y < Board_width && list + i * x > 0 && list + i * x < Board_width && data->chessMap[row + i * y][list + i * x] == -1)
						{
							botNum++;
						}
						else if (row + i * y > 0 && row + i * y < Board_width && list + i * x > 0 && list + i * x < Board_width && data->chessMap[row + i * y][list + i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else
							break;
					}

					//�԰��巴������
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y > 0 && row - i * y < Board_width && list - i * x > 0 && list - i * x < Board_width && data->chessMap[row - i * y][list - i * x] == -1)
						{
							botNum++;
						}

						//�հ�λ
						else if (row - i * y > 0 && row - i * y < Board_width && list - i * x > 0 && list - i * x < Board_width && data->chessMap[row - i * y][list - i * x] == 0)
						{
							emptyNum++;
							break;
						}
						else //���߽�
						{
							break;
						}
					}

					if (botNum == 0) //��ͨ����
						data->scoreMap[row][list] += 5;
					else if (botNum == 1) //ɱ��
						data->scoreMap[row][list] += 10;
					else if (botNum == 2) {
						if (emptyNum == 1) //����
							data->scoreMap[row][list] += 25;
						else if (emptyNum == 2) //����
							data->scoreMap[row][list] += 50;
					}
					else if (botNum == 3) {
						if (emptyNum == 1) //����
							data->scoreMap[row][list] += 55;
						else if (emptyNum == 2) //����
							data->scoreMap[row][list] += 300;
					}

					else if (botNum >= 4)
						data->scoreMap[row][list] += 30000;
				}

			}
		}
	}
}

//��������
point_t actionByAI(ChessData * data)
{
	caculateScore(data);
	//������������������λ��
	int maxScore = 0;
	point_t maxPoints[Board_width * Board_width] = { 0 };
	int k = 0;
	for (int row = 0; row < Board_width; row++)
		for (int list = 0; list < Board_width; list++)
		{
			//ǰ������������ǿյ�
			if (data->chessMap[row][list] == 0)
			{
				if (data->scoreMap[row][list] > maxScore)
				{
					memset(maxPoints, 0, sizeof(maxPoints));
					k = 0;
					maxScore = data->scoreMap[row][list];
					maxPoints[k].row = row;
					maxPoints[k].list = list;
					k++;
				}
				else if (data->scoreMap[row][list] == maxScore) {
					maxPoints[k].row = row;
					maxPoints[k].list = list;
					k++;
				}
			}
		}

	srand((unsigned)time(0));
	int index = rand() % k;
	return maxPoints[index];
}

//AI����
void AI_GO()
{
	point_t point = actionByAI(&game);
	clickRow = point.row;
	clickList = point.list;
	Sleep(1000);//AI��װ˼��
	chessDown(clickRow, clickList, -1);
	updataGameMap(&game, clickRow, clickList);
}

//ʤ���ж�  ���ڲ�������
bool checkWin(ChessData* game, int row, int list)
{
	//����б��б���ִ������ÿ����������ݵ�ǰ��������������5�����ӣ���һ�ַ��Ͼ���Ӯ
	//ˮƽ����
	for (int i = 0; i < 5; i++) {
		//����5��������ƥ��4����20�����
		if (list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 1] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 2] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 3] &&
			game->chessMap[row][list - i] == game->chessMap[row][list - i + 4])

			return true;
	}

	//��ֱ������������4��
	for (int i = 0; i < 5; i++) {
		if (list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 1][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 2][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 3][list] &&
			game->chessMap[row - i][list] == game->chessMap[row - i + 4][list])

			return true;
	}

	//��б�߷���
	for (int i = 0; i < 5; i++) {
		if (row + i < Board_width &&
			row + i - 4 >= 0 &&
			list - i + 4 < Board_width &&
			//��[row+i]�У���[col-i]�����ӣ������Ϸ�������4�����Ӷ���ͬ
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 1][list - i + 1] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 2][list - i + 2] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 3][list - i + 3] &&
			game->chessMap[row + i][list - i] == game->chessMap[row + i - 4][list - i + 4])

			return true;
	}

	//"\"����
	for (int i = 0; i < 5; i++) {
		//��[row+i]�У���[col-i]�е����ӣ������·��������ĸ����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < Board_width &&
			list - i >= 0 &&
			list - i + 4 < Board_width &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 1][list - i + 1] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 2][list - i + 2] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 3][list - i + 3] &&
			game->chessMap[row - i][list - i] == game->chessMap[row - i + 4][list - i + 4])

			return true;
	}
	return false;
}

//���� ���� �رմ���
bool checkOver() //�����Ϸ�Ƿ����
{
	if (checkWin(&game, clickRow, clickList)) {
		Sleep(1000);
		//����Ӯ����ʱ����Ѿ���ת���ֵ���������
		if (game.playerFlag == false) {
			mciSendString(L"play shengli.mp3", 0, 0, 0);
			loadimage(0, L"shengli.png");
		}
		else
		{
			mciSendString(L"play shibai.mp3", 0, 0, 0);
			loadimage(0,L"shibai.png");
		}

		Sleep(5000);
		closegraph();
		return true;
	}
	return false;
}
bool checkOver2()//�����Ϸ�Ƿ����
{
	if (checkWin(&game, clickRow, clickList)) {
		Sleep(1000);
		//����Ӯ����ʱ����Ѿ���ת���ֵ���������
		if (game.playerFlag == false) {
			mciSendString(L"play win.mp3", 0, 0, 0);
			loadimage(0,L"heiwin.png");
		}
		else
		{
			mciSendString(L"play win.mp3", 0, 0, 0);
			loadimage(0, L"baiwin.png");
		}

		Sleep(5000);
		closegraph();
		return true;
	}
	return false;
}

//���˶�ս
void renren()
{
	int n = 1;
	while (1)
	{   //���
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && clickDIM(msg))//���
		{
			manGO(n);
			checkOver2();
			n *= -1;
		}
	}
}

//��ji��ս
void renji()
{
	while (1)
	{   //���
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && clickDIM(msg))//���
		{
			manGO(1);
			checkOver();

			AI_GO();
			checkOver();
		}
	}
}

int main(void)
{

	if (kaijv())
	{
		init();
		renji();
	}
	else
	{
		init();
		renren();
	}

	system("pause");
	return 0;
}

