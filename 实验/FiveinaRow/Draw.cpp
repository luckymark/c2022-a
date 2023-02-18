#include "title.h"

IMAGE backImg;	

void drawPiece(int x, int y, int color)
{
	if (color == white)
	{
		setfillcolor(WHITE); 
	}
	else if (color == black)
	{
		setfillcolor(BLACK); 
	}
	fillcircle(x * piece_size + offsetx, y * piece_size + offsety, piece_size / 2);   //�����xӦ���Ǵ�����������x
	
}

void drawBoard()
{
	initgraph(520, 520); 
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT);  

	settextstyle(55, 0, L"����");   
	settextcolor(RGB(70, 70, 70)); 
	outtextxy(270, 130, L"��Ҷ�ս");   
	outtextxy(320, 200, L"AI��ս");
	outtextxy(320, 270, L"AIVSAI");
	
}

void drawBoard2()
{
	initgraph((map_width - 1) * piece_size + offsetx * 2, (map_height - 1) * piece_size + offsety * 4);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	for (int i = 0; i < map_width; i++)
	{
		line(i * piece_size + offsetx, offsety, i * piece_size + offsetx, offsety + (map_height - 1) * piece_size);
	}
	for (int i = 0; i < map_height; i++)
	{
		line(offsetx, offsety + i * piece_size, (map_width - 1) * piece_size + offsetx, offsety + i * piece_size);
	}
}

void clear(int x,int y)
{
		/*�����С�����εķ�ʽ���Բ����ֹ���±���*/
		clearrectangle(x * piece_size + offsetx - (piece_size / 2), y * piece_size + offsety - (piece_size / 2), x * piece_size + offsetx + (piece_size / 2), y * piece_size + offsety + (piece_size / 2));   //��������
		if ((x == 0) || (y == 0) || (x == 14) || (y == 14))    //�����̱�Ե����
		{
			line(x * piece_size + offsetx - (piece_size / 2), offsety + y * piece_size, x * piece_size + offsetx + (piece_size / 2), offsety + y * piece_size);
			line(offsetx + x * piece_size, y * piece_size + offsety - (piece_size / 2), offsetx + x * piece_size, y * piece_size + offsety + (piece_size / 2));
			/*����ಹ����*/
			clearrectangle(offsetx-piece_size/2,offsety,offsetx,offsety + 14 * piece_size);       
			clearrectangle(offsetx,offsety+14*piece_size,offsetx+14*piece_size,offsety+14*piece_size+piece_size/2);
			clearrectangle(offsetx + 14 * piece_size, offsety, offsetx + 14 * piece_size+piece_size/2, offsety+14*piece_size);
			clearrectangle(offsetx,offsety,offsetx+14*piece_size,offsety-piece_size / 2);
			/* �����Ե����*/
			line(offsetx, offsety, offsetx, offsety + 14 * piece_size);            
			line(offsetx, offsety + 14 * piece_size, offsetx+14*piece_size, offsety + 14 * piece_size);
			line(offsetx + 14 * piece_size, offsety , offsetx + 14 * piece_size, offsety + 14 * piece_size);
			line(offsetx, offsety, offsetx + 14 * piece_size, offsety);
		}
		else              
		{
			/*�������*/
			line(x * piece_size + offsetx - (piece_size / 2), offsety + y * piece_size, x * piece_size + offsetx + (piece_size / 2), offsety + y * piece_size);
			line(offsetx + x * piece_size, y * piece_size + offsety - (piece_size / 2), offsetx + x * piece_size, y * piece_size + offsety + (piece_size / 2));
		}
}

void regret(void)
{
	if ((num != 0)&&(num!=1))
	{
		for (int i = 0; i <= 14; i++)
		{
			for (int j = 0; j <= 14; j++)
			{
				if (order[i][j] == num)
				{
					clear(i, j);
					order[i][j] = 0;
					num = num - 1;
					map[i][j] = 0;        //����λ����Ϣ
					Piece += changePiece;
					changePiece *= -1;    //�ı�������ɫ

					jump = 1;        //����ֹͣѭ�����ôε���»������
					break;
				}
			}
			if (jump == 1)
			{
				jump = 0;
				break;
			}
		}
	}
}

