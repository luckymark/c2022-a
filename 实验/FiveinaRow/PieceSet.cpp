#include "title.h"

int map[20][20] = { 0 };
int check = 0;



// 放置棋子，返回true表示放置成功，false 表示放置失败
bool pieceSet(int x, int y, int color)
{
	if ((map[x][y] != 0)|| (x < 0) || (x > 14) || (y < 0) || (y > 14))   //当前位置有棋子或越界
	{
		return false;
	}
	map[x][y] = color;
	return true;
}


void judge(int x, int y)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++) 
		{
			if (map[x][y] == 1)
			{
				if ((x + i >= 0) && (x + i <= 14) && (y + j >= 0) && (y + j <= 14) && (map[x + i][y + j] == 1))   //不越界控制
				{
					if ((i == 0) && (j == 0))
					{
						continue;
					}
					if ((x + 2 * i >= 0) && (x + 2 * i <= 14) && (y + 2 * j >= 0) && (y + 2 * j <= 14) && (map[x + 2 * i][y + 2 * j] == 1))
					{
						if ((x + 3 * i >= 0) && (x + 3 * i <= 14) && (y + 3 * j >= 0) && (y + 3 * j <= 14) && (map[x + 3 * i][y + 3 * j] == 1))
						{
							if ((x + 4 * i >= 0) && (x + 4 * i <= 14) && (y + 4 * j >= 0) && (y + 4 * j <= 14) && (map[x + 4 * i][y + 4 * j] == 1))
							{
								check = 1;
								break;
							}
							else
							{
								if ((map[x - i][y - j] == 1) && (x - i >= 0) && (x - i <= 14) && (y - j >= 0) && (y - j <= 14))
								{
									check = 1;
									break;
								}
							}
						}
						else
						{
							if ((map[x - i][y - j] == 1) && (map[x - 2 * i][y - 2 * j] == 1) && (x - 2 * i >= 0) && (x - 2 * i <= 14) && (y - 2 * j >= 0) && (y - 2 * j <= 14))
							{
								check = 1;
								break;
							}
						}
					}
					else
					{
						if ((map[x - i][y - j] == 1) && (map[x - 2 * i][y - 2 * j] == 1) && (map[x - 3 * i][y - 3 * j] == 1) && (x - 3 * i >= 0) && (x - 3 * i <= 14) && (y - 3 * j >= 0) && (y - 3 * j <= 14))
						{
							check = 1;
							break;
						}
					}
				}
			}
			if (map[x][y] == 2)
			{
				if ((x + i >= 0) && (x + i <= 14) && (y + j >= 0) && (y + j <= 14) && (map[x + i][y + j] == 2))
				{
					if ((i == 0) && (j == 0))
					{
						continue;
					}
					if ((x + 2 * i >= 0) && (x + 2 * i <= 14) && (y + 2 * j >= 0) && (y + 2 * j <= 14) && (map[x + 2 * i][y + 2 * j] == 2))
					{
						if ((x + 3 * i >= 0) && (x + 3 * i <= 14) && (y + 3 * j >= 0) && (y + 3 * j <= 14) && (map[x + 3 * i][y + 3 * j] == 2))
						{
							if ((x + 4 * i >= 0) && (x + 4 * i <= 14) && (y + 4 * j >= 0) && (y + 4 * j <= 14) && (map[x + 4 * i][y + 4 * j] == 2))
							{
								check = 2;
								break;
							}
							else
							{
								if ((map[x - i][y - j] == 2) && (x - i >= 0) && (x - i <= 14) && (y - j >= 0) && (y - j <= 14))
								{
									check = 2;
									break;
								}
							}
						}
						else
						{
							if ((map[x - i][y - j] == 2) && (map[x - 2 * i][y - 2 * j] == 2) && (x - 2 * i >= 0) && (x - 2 * i <= 14) && (y - 2 * j >= 0) && (y - 2 * j <= 14))
							{
								check = 2;
								break;
							}
						}
					}
					else
					{
						if ((map[x - i][y - j] == 2) && (map[x - 2 * i][y - 2 * j] == 2) && (map[x - 3 * i][y - 3 * j] == 2) && (x - 3 * i >= 0) && (x - 3 * i <= 14) && (y - 3 * j >= 0) && (y - 3 * j <= 14))
						{
							check = 2;
							break;
						}
					}
				}

			}
		}
	}

}