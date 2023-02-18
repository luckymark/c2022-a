#include "title.h"

int map[20][20] = { 0 };
int check = 0;



 /*�������ӣ�����true��ʾ���óɹ���false ��ʾ����ʧ��*/
bool pieceSet(int x, int y, int color)
{
	if ((map[x][y] != 0)|| (x < 0) || (x > 14) || (y < 0) || (y > 14))   //��ǰλ�������ӻ�Խ��
	{
		return false;
	}
	map[x][y] = color;
	return true;
}


void judge(int x, int y,int color)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)         //����Χ���������ж��Ƿ��������
		{
			if ((x + i >= 0) && (x + i <= 14) && (y + j >= 0) && (y + j <= 14) && (map[x + i][y + j] == color))   //��Խ������Χ��ͬɫ����
			{
				if ((i == 0) && (j == 0))    //ȥ���õ㱾��
				{
					continue;
				}
				if ((x + 2 * i >= 0) && (x + 2 * i <= 14) && (y + 2 * j >= 0) && (y + 2 * j <= 14) && (map[x + 2 * i][y + 2 * j] == color))
				{
					if ((x + 3 * i >= 0) && (x + 3 * i <= 14) && (y + 3 * j >= 0) && (y + 3 * j <= 14) && (map[x + 3 * i][y + 3 * j] == color))
					{
						if ((x + 4 * i >= 0) && (x + 4 * i <= 14) && (y + 4 * j >= 0) && (y + 4 * j <= 14) && (map[x + 4 * i][y + 4 * j] == color))
						{
							check = color;
							break;
						}
						else
						{
							if ((map[x - i][y - j] == color) && (x - i >= 0) && (x - i <= 14) && (y - j >= 0) && (y - j <= 14))
							{
								check = color;
								break;
							}
						}
					}
					else
					{
						if ((map[x - i][y - j] == color) && (map[x - 2 * i][y - 2 * j] == color) && (x - 2 * i >= 0) && (x - 2 * i <= 14) && (y - 2 * j >= 0) && (y - 2 * j <= 14))
						{
							check = color;
							break;
						}
					}
				}
				else
				{
					if ((map[x - i][y - j] == color) && (map[x - 2 * i][y - 2 * j] == color) && (map[x - 3 * i][y - 3 * j] == color) && (x - 3 * i >= 0) && (x - 3 * i <= 14) && (y - 3 * j >= 0) && (y - 3 * j <= 14))
					{
						check = color;
						break;
					}
				}
			}
			
			
		}
	}

}