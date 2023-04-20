#include"all.h"
extern int Chess[ROW][LINE];

extern int mm ;
extern int	n ;
int X;
int Y;
int box[40][3] = { 0 };
int memory[30] = { 0 };


int monitor[11] = { 0 };




int five[5][7] =  {0,2,2,2,2,2,0,
                   2,2,2,2,2,0,0,
	               2,2,2,2,0,0,0,
                   0,0,2,2,2,2,2,
                   0,0,0,2,2,2,2};
int five2[7] = { 0,1,1,1,1,1,0 };
int five3[7] = { 1,1,1,1,1,0,0 };//10000000


int four[4][7] ={0,2,2,2,2,0,0,
                  2,2,2,2,0,0,0,
	              0,0,2,2,2,2,0,
	              0,0,0,2,2,2,2};
int four2[7] = { 0,1,1,1,1,0,0 };
int four3[7] = { 1,1,1,1,0,0,0 };
int four4[7] = { 0,0,0,1,1,1,1 };//1000000


int cfour[6][7] = {1,2,2,2,2,0,0,
                    0,1,2,2,2,2,0,
	                0,0,1,2,2,2,2,
	                2,2,2,1,0,0,0,
	                2,2,2,2,1,0,0,
	                0,2,2,2,2,1,0 };
int cfour2[7] = { 0,2,1,1,1,1,0 };
int cfour3[7] = { 0,0,2,1,1,1,1 };
int cfour4[7] = { 1,1,1,1,2,0,0 };
int cfour5[7] = { 0,1,1,1,1,2,0 };
int cfour6[7] = { 0,0,1,1,1,1,2 };//10000//后续可以改良为二维数组



int three[3][7] = { 0,2,2,2,0,0,0,
                    0,0,2,2,2,0,0,
	                0,0,0,2,2,2,0};
int three2[7] = { 0,0,1,1,1,0,0 };
int three3[7] = { 0,0,0,1,1,1,0 };//8000


int dthree[6][7] = { 1,2,2,2,0,0,0, 
                     0,1,2,2,2,0,0,
	                 0,0,1,2,2,2,0,
	                 0,0,0,2,2,2,1,
	                 0,0,2,2,2,1,0,
	                 0,2,2,2,1,0,0,};
int dthree2[7] = { 0,2,1,1,1,0,0 };
int dthree3[7] = { 0,0,2,1,1,1,0 };
int dthree4[7] = { 0,0,0,1,1,1,2 };
int dthree5[7] = { 0,0,1,1,1,2,0 };
int dthree6[7] = { 0,1,1,1,2,0,0 };//1000



int two[2][7] = {0,0,0,2,2,0,0,
                 0,0,2,2,0,0,0 };
int two2[7] = { 0,0,1,1,0,0,0 };//800

int dtwo[4][7] = { 0,0,1,2,2,0,0,
                   0,1,2,2,0,0,0 , 
	               0,0,2,2,1,0,0 ,
	               0,0,0,2,2,1,0 };
int dtwo2[7] = { 0,2,1,1,0,0,0 };
int dtwo3[7] = { 0,0,1,1,2,0,0 };
int dtwo4[7] = { 0,0,0,1,1,2,0 };//50

int done[2][7] = { 0,0,0,2,1,0,0,
                   0,0,1,2,0,0,0 };
int done2[7] = { 0,0,2,1,0,0,0 };//10







 
int judge(int num,int block)
{
	if (num == 5)
		return 10000000;
	if (num == 4 && block == 0)
		return 1000000;
	if (num == 4 && block == 1)
		return 10000;
	if (num == 3 && block == 0)
		return 8000;
	if (num == 3&& block == 1)
	{
		return 1000;
	}
	if (num == 2 && block == 0)
	{
		return 800;
	}
	if (num == 2 && block == 1)
	{
		return 50;
	}
	else
		return 10;
}









int evaluate(int Chess[][15], int m, int n)
{

	int num = 1;
	int block =0;
	int point = 0;
	if (Chess[m][n + 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m][n + i] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	if (Chess[m][n - 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m][n - i] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	//左右
	point += judge(num, block);
	num = 1;
	block = 0;
	if (Chess[m+1][n] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m+i][n] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	if (Chess[m - 1][n] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m - i][n] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	//上下
	///先找到相同的，再去循环
	point += judge(num,block);
	num = 1;
	block = 0;
	if (Chess[m + 1][n + 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m + i][n + i] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	if (Chess[m - 1][n - 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m - i][n - i] != Chess[m][n])
			{
				block++;
				break;
			}
			else
				num++;
		}
	}
	// "\"方向
	num = 1;
	block = 0;
	point += judge(num, block);
	if (Chess[m + 1][n - 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m + i][n - i] != Chess[m][n])
			{
				block;
				break;
			}
			else
				num++;
		}
	}
	if (Chess[m - 1][n + 1] == Chess[m][n])
	{
		for (int i = 1; i < 5; i++)
		{
			if (Chess[m - i][n + i] != Chess[m][n])
			{
				block;
				break;
			}
			else
				num++;
		}
	}
	// "/"方向
	point += judge(num, block);
	return point;
}






void dfs(int* row,int* line)
{
	int p = 0;
	int max = 0, num = 0, max1 = 0;
	int p1 = 0, p2 = 0;
	int a = 0, b = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (Chess[i][j] != 0)
			{
				num++;
			}
		}
		if (num>1)
			break;
	}
	if (num == 0||(num == 1&&Chess[7][7] == 1))
	{
		srand((unsigned)time(NULL));
		*row = 7/*rand()%14*/;
		*line = 7/*rand()%14*/;
		if (Chess[7][7] == 1)
			(*row)++;
	}
	else
	{
		memset(memory, 0, sizeof(memory));
		memset(box, 0, sizeof(box));
		Minmax(Chess, NGIF, PTIF, 2, 0);
		*row = X;
		*line = Y;
		//dfs1(0,1000000,-10000000,0,0,0,row,line);
	}
	Chess[*row][*line] = 2;
	printf("(%d,%d) %d\n", *row, *line, 2);
}



void dfs1(int depth, int min_cut, int max_cut,int num,int all_point,int cur_point,int *row,int *line)
{
	if (depth == 3)
	{
		if (all_point > memory[0])
		{
			memory[0] = all_point;
			*row = box[0][0];
			*line = box[0][1];
		}
	}
	else
	{
		for (int i = 1; i < 14; i++)
		{
			for (int j = 1; j < 14; j++)
			{
				if (Chess[i][j] == 0)
				{
					if (num % 2 == 0)
					{
						Chess[i][j] = 2;
						cur_point = evaluate(Chess, i, j);
					}
					else
					{
						Chess[i][j] = 1;
						cur_point = -evaluate(Chess, i, j);
					}
					box[depth][0] = i;
					box[depth][1] = j;
				    dfs1(depth + 1, min_cut, max_cut, num + 1, all_point + cur_point, cur_point, row, line);
					Chess[i][j] = 0;
				}
			}
		}
	}
}//或许用树的结构可能会好一些





//
//int dfs1(int depth, int min_cut, int max_cut, int num, int all_point, int cur_point, int* row, int* line)
//{
//	if (depth == 3)
//	{
//		if (all_point > memory[0])
//		{
//			memory[0] = all_point;
//			*row = box[0][0];
//			*line = box[0][1];
//		}
//		if (max_cut < cur_point)
//		{
//			max_cut = cur_point;
//		}
//		return max_cut;
//	}
//	else
//	{
//		for (int i = 0; i < 15; i++)
//		{
//			for (int j = 0; j < 15; j++)
//			{
//				if (num % 2 == 0)
//				{
//					Chess[i][j] = 2;
//					cur_point = evaluate(Chess, i, j);
//				}
//				else
//				{
//					Chess[i][j] = 1;
//					cur_point = evaluate(Chess, i, j);
//				}
//				box[depth][0] = i;
//				box[depth][1] = j;
//				if (depth % 2 == 0)
//				{
//					int max = dfs1(depth + 1, min_cut, max_cut, num + 1, all_point + cur_point, cur_point, row, line);
//					max_cut = (max > max_cut) ? max : max_cut;
//				}
//				else
//				{
//					int min = dfs1(depth + 1, min_cut, max_cut, num + 1, all_point - cur_point, cur_point, row, line);
//					min_cut = (min < min_cut) ? min : min_cut;
//				}
//				Chess[i][j] = 0;
//				if (min_cut < max_cut)
//				{
//					if (depth % 2 == 1)
//						return max_cut;
//					else
//						return min_cut;
//				}
//			}
//		}
//	}
//	if (depth % 2 == 1)
//		return max_cut;
//	else
//		return min_cut;
//}