#include <E:\c\FiveinaLow\title.h>


int AIx, AIy;
int zero[20][20] = { 0 };
int dcheck1[20][20] = { 0 }, dcheck2[20][20] = { 0 }, dcheck3[20][20] = { 0 }, dcheck4[20][20] = { 0 };
int maxmark = 0, mark = 0, skip = 0, defendx = 0, defendy = 0, defend = 0;

void relief(int x[20][20], int y[20][20])
{
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			x[i][j] = y[i][j];
		}

	}
}

void AI(int x, int y)
{

	for (int i = -5; i <= 5; i++)     //在对方落点正负五格内进行判断
	{
		for (int j = -5; j <= 5; j++)
		{
			if (map[x + i][y + j] == 0)   //空位
			{
				if ((x + i < 0) || (x + i > 14) || (y + j < 0) || (y + j > 14))
				{
					continue;
				}


				/*进攻评估*/
				map[x + i][y + j] = 1;     
				judge(x + i, y + j,1);
				if (check == 1)        	
				{
					AIx = x + i, AIy = y + j;
					skip = 1;
					check = 0;
					defend = 0;
					break;
				}
				else
				{

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0)   
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 1;
								judge(x + i + k, y + j + l,1);
								if (check == 1)      
								{
									mark += 20000;      
									dcheck1[x + i + k][y + j + l] = 1;        
								}
								check = 0;
								map[x + i + k][y + j + l] = 0;     //清空kl轮的计算值
							}

						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck1[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 1;
								for (int m = -4; m <= 4; m++)
								{
									for (int n = -4; n <= 4; n++)
									{
										if ((map[x + i + m][y + j + n] == 0) && (dcheck1[x + i + m][y + j + n] != 1))   //第二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 1;
											judge(x + i + m, y + j + n,1);
											if (check == 1)      
											{
												mark += 2000;
												dcheck2[x + i + m][y + j + n] = 1;
											}
											check = 0;
											map[x + i + m][y + j + n] = 0;


										}

									}

								}
								map[x + i + k][y + j + l] = 0;
							}
						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck1[x + i + k][y + j + l] != 1) && (dcheck2[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 1;

								for (int m = -4; m <= 4; m++)
								{
									for (int n = -4; n <= 4; n++)
									{
										if ((map[x + i + m][y + j + n] == 0) && (dcheck1[x + i + m][y + j + n] != 1) && (dcheck2[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 1;

											for (int o = -4; o <= 4; o++)
											{
												for (int p = -4; p <= 4; p++)
												{
													if (map[x + i + o][y + j + p] == 0 && (dcheck1[x + i + o][y + j + p] != 1) && (dcheck2[x + i + o][y + j + p] != 1))
													{
														if ((x + i + o < 0) || (x + i + o > 14) || (y + j + p < 0) || (y + j + p > 14))
														{
															continue;
														}
														map[x + i + o][y + j + p] = 1;
														judge(x + i + o, y + j + p,1);
														if (check == 1)      
														{
															mark += 15;
														}

														check = 0;
														map[x + i + o][y + j + p] = 0;


													}

												}

											}

											map[x + i + m][y + j + n] = 0;


										}

									}

								}
								map[x + i + k][y + j + l] = 0;
							}
						}
					}
				}
				relief(dcheck1, zero);    //清空攻击轮复用检查
				relief(dcheck2, zero);
				check = 0;
				map[x + i][y + j] = 0;



				/*防守评估*/
				map[x + i][y + j] = 2;
				judge(x + i, y + j,2);
				if (check == 2)        	
				{
					defendx = x + i;
					defendy = y + j;
					defend = 1;        //不能直接跳出循环，以防进攻上有必杀未循环到
					check = 0;
				}
				else
				{

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0)   //空位
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 2;
								judge(x + i + k, y + j + l,2);
								if (check == 2)      //第一步有必杀情况
								{
									mark += 20000;
									dcheck3[x + i + k][y + j + l] = 1;      //计入复用检查
								}
								check = 0;
								map[x + i + k][y + j + l] = 0;     //清空kl轮的计算值
							}

						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck3[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 2;
								for (int m = -4; m <= 4; m++)
								{
									for (int n = -4; n <= 4; n++)
									{
										if ((map[x + i + m][y + j + n] == 0) && (dcheck3[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 2;
											judge(x + i + m, y + j + n,2);
											if (check == 2)      
											{
												mark += 3000;
												dcheck4[x + i + m][y + j + n] = 1;   
											}
											check = 0;
											map[x + i + m][y + j + n] = 0;


										}

									}

								}
								map[x + i + k][y + j + l] = 0;
							}
						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck3[x + i + k][y + j + l] != 1) && (dcheck4[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 2;

								for (int m = -4; m <= 4; m++)
								{
									for (int n = -4; n <= 4; n++)
									{
										if ((map[x + i + m][y + j + n] == 0) && (dcheck3[x + i + m][y + j + n] != 1) && (dcheck4[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 2;

											for (int o = -4; o <= 4; o++)
											{
												for (int p = -4; p <= 4; p++)
												{
													if (map[x + i + o][y + j + p] == 0 && (dcheck3[x + i + o][y + j + p] != 1) && (dcheck4[x + i + o][y + j + p] != 1))   //空位
													{
														if ((x + i + o < 0) || (x + i + o > 14) || (y + j + p < 0) || (y + j + p > 14))
														{
															continue;
														}
														map[x + i + o][y + j + p] = 2;
														judge(x + i + o, y + j + p,2);
														if (check == 2)     
														{
															mark += 20;
														}

														check = 0;
														map[x + i + o][y + j + p] = 0;


													}

												}

											}

											map[x + i + m][y + j + n] = 0;


										}

									}

								}
								map[x + i + k][y + j + l] = 0;
							}
						}
					}
				}
				relief(dcheck3, zero);
				relief(dcheck4, zero);
				check = 0;
				map[x + i][y + j] = 0;



				if (mark > maxmark)
				{
					maxmark = mark;
					AIx = x + i, AIy = y + j;     //更新最高分数与最优位置
				}
				mark = 0;


			}

		}
		/*跳出第二层循环*/
		if (skip == 1)
		{
			break;
		}
	}

	/*平局输出*/
	if (maxmark == 0)
	{
		check = 3;
	}

	/*确定没有必杀后，输出必防*/
	if (defend == 1)
	{
		AIx = defendx;
		AIy = defendy;
	}





}


	




