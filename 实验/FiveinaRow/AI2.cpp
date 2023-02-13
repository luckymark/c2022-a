#include "title.h"


int AI2x, AI2y;
int zero2[20][20] = { 0 };
int dcheck5[20][20] = { 0 }, dcheck6[20][20] = { 0 }, dcheck7[20][20] = { 0 }, dcheck8[20][20] = { 0 };

void relief2(int x[20][20], int y[20][20])
{
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			x[i][j] = y[i][j];
		}

	}
}

//复制AI后的先手黑棋AI2，由于初期设计时直接让1，2表示棋子颜色而非变量值，导致ctrlc ctrlv的效率更高...长长教训
//设计AI2的目的是为了实现AI对下，通过录屏慢放找到落子的不合理之处
void AI2(int x, int y)
{
	int maxmark = 0, mark = 0, skip = 0;
	for (int i = -5; i <= 5; i++)
	{
		for (int j = -5; j <= 5; j++)
		{
			if (map[x + i][y + j] == 0)   //空位
			{
				if ((x + i < 0) || (x + i > 14) || (y + j < 0) || (y + j > 14))
				{
					continue;
				}


			

				//进攻评估
				map[x + i][y + j] = 2;
				judge(x + i, y + j);
				if (check == 2)        	//必杀
				{
					AI2x = x + i, AI2y = y + j;
					skip = 1;
					check = 0;
					break;
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
								judge(x + i + k, y + j + l);
								if (check == 2)      
								{
									mark += 2000000;    
									dcheck7[x + i + k][y + j + l] = 1;
								}
								check = 0;
								map[x + i + k][y + j + l] = 0;     //清空第一轮的计算值
							}

						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck7[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
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
										if ((map[x + i + m][y + j + n] == 0) && (dcheck7[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 2;
											judge(x + i + m, y + j + n);
											if (check == 2)      //第二步有必杀情况
											{
												mark += 300000;
												dcheck8[x + i + m][y + j + n] = 1;   //第二轮必杀一次
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
							if (map[x + i + k][y + j + l] == 0 && (dcheck7[x + i + k][y + j + l] != 1) && (dcheck8[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
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
										if ((map[x + i + m][y + j + n] == 0) && (dcheck7[x + i + m][y + j + n] != 1) && (dcheck8[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
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
													if (map[x + i + o][y + j + p] == 0 && (dcheck7[x + i + o][y + j + p] != 1) && (dcheck8[x + i + o][y + j + p] != 1))   //下一轮的空位
													{
														if ((x + i + o < 0) || (x + i + o > 14) || (y + j + p < 0) || (y + j + p > 14))
														{
															continue;
														}
														map[x + i + o][y + j + p] = 2;
														judge(x + i + o, y + j + p);
														if (check == 2)      //第三步有必杀情况
														{
															mark += 2000;
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
				relief2(dcheck7, zero2);
				relief2(dcheck8, zero2);
				check = 0;
				map[x + i][y + j] = 0;






				//防守评估
				map[x + i][y + j] = 1;
				judge(x + i, y + j);
				if (check == 1)        	//被必杀
				{
					AI2x = x + i, AI2y = y + j;
					skip = 1;
					check = 0;
					break;
				}
				else
				{

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0)   //下一轮的空位
							{
								if ((x + i + k < 0) || (x + i + k > 14) || (y + j + l < 0) || (y + j + l > 14))
								{
									continue;
								}
								map[x + i + k][y + j + l] = 1;
								judge(x + i + k, y + j + l);
								if (check == 1)      //第一轮有必杀情况
								{
									mark += 2000000;   
									dcheck5[x + i + k][y + j + l] = 1;
								}
								check = 0;
								map[x + i + k][y + j + l] = 0;     //清空第一轮的计算值
							}

						}
					}

					for (int k = -4; k <= 4; k++)
					{
						for (int l = -4; l <= 4; l++)
						{
							if (map[x + i + k][y + j + l] == 0 && (dcheck5[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
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
										if ((map[x + i + m][y + j + n] == 0) && (dcheck5[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
										{
											if ((x + i + m < 0) || (x + i + m > 14) || (y + j + n < 0) || (y + j + n > 14))
											{
												continue;
											}
											map[x + i + m][y + j + n] = 1;
											judge(x + i + m, y + j + n);
											if (check == 1)      //第二步有必杀情况
											{
												mark += 200000;
												dcheck6[x + i + m][y + j + n] = 1;   
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
							if (map[x + i + k][y + j + l] == 0 && (dcheck5[x + i + k][y + j + l] != 1) && (dcheck6[x + i + k][y + j + l] != 1))   //周围空位且复用检查通过
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
										if ((map[x + i + m][y + j + n] == 0) && (dcheck5[x + i + m][y + j + n] != 1) && (dcheck6[x + i + m][y + j + n] != 1))   //二步空位且复用检查通过
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
													if (map[x + i + o][y + j + p] == 0 && (dcheck5[x + i + o][y + j + p] != 1) && (dcheck6[x + i + o][y + j + p] != 1))   //空位
													{
														if ((x + i + o < 0) || (x + i + o > 14) || (y + j + p < 0) || (y + j + p > 14))
														{
															continue;
														}
														map[x + i + o][y + j + p] = 1;
														judge(x + i + o, y + j + p);
														if (check == 1)      //第三步有必杀情况
														{
															mark += 1500;
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
				relief2(dcheck5, zero2);
				relief2(dcheck6, zero2);
				check = 0;
				map[x + i][y + j] = 0;




				if (mark > maxmark)
				{
					maxmark = mark;
					AI2x = x + i, AI2y = y + j;     //更新最高分数与最优位置
				}
				mark = 0;
				if (maxmark == 0)
				{
					check = 3;
				}
				

			}

		}
		if (skip == 1)
		{
			break;
		}
	}
}