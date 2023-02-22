

#include "Chess.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<mmsystem.h>
#include<math.h>
#include"AI.h"
#pragma comment(lib,"winmm.lib")
IMAGE gImage;

void putimagePNG(int x, int y, IMAGE* picture);



void Chess::init()
{
	//������Ϸ����
	initgraph(CHESSMAP_WIDTH, CHESSMAP_HEIGHT, EX_SHOWCONSOLE);

	//��������ͼƬ
	//loadimage(&gImage, _T("chessMap.png"), 800, 804, true);
	loadimage(&gImage, _T("box\\OIP-C.jfif"), PICTURE_WIDTH, PICTURE_HEIGHT, true);
	
	//��ʾ����ͼƬ
	//putimage(0, 0, &gImage);
	putimage(0, 0, &gImage);
	setfillcolor(background);
	fillrectangle(PICTURE_WIDTH,PICTURE_HEIGHT,CHESSMAP_WIDTH,0);

	setfillcolor(WHITE);
	fillrectangle(PICTURE_WIDTH+50, PICTURE_HEIGHT-150, CHESSMAP_WIDTH-50, 400);
	settextstyle(25, 15, "��Բ");
	outtextxy(PICTURE_WIDTH + 50 +25, PICTURE_HEIGHT - 150-35, "����");
	
	fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 250, CHESSMAP_WIDTH - 50, 300);
	outtextxy(PICTURE_WIDTH + 50 + 25, PICTURE_HEIGHT - 250 - 35, "����");

	fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 350 , CHESSMAP_WIDTH - 50, 200);
	outtextxy(PICTURE_WIDTH + 50 + 25, PICTURE_HEIGHT - 350 - 35, "����");
	//������Ч
	//mciSendString("play start.mp3", NULL, 0, NULL);

	//���غڰ�����ͼƬ�����б���  
	//loadimage(&blackchessImg, _T("blackchessImg.jpg"), chesssize, chesssize, true);
	//loadimage(&whitechessImg, _T("whitechessImg.jpg"), chesssize, chesssize, true);
	loadimage(&blackchessImg, _T("box\\����.png"), chesssize, chesssize, true);
	loadimage(&whitechessImg, _T("box\\����.png"), chesssize, chesssize, true);
	loadimage(&smallmap, _T("box\\smallmap.png"), chesssize, chesssize, true);
	changEchessif = 0;
	gobacktimes= 3;
	//������̱��棬Ϊ��һ����׼��
	for (int i = 0; i < gradesize; i++)
	{
		for (int j = 0; j < gradesize; j++)
		{
			chessmap[i][j] = 0;
		}
	}
	if (changchessif == 0) {
		//���忪�ֺڷ�����
		playerFlag = CHESS_BLACK;
	}
	else if(changchessif == 1)
	{
		playerFlag = false;
	}

	
}

//����
void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	backlist.insert(backlist.begin(), *pos);
	if (backlist.size() > 6) {
		backlist.pop_back();
	}
	//����
	int x = margin_x + chesssize * pos->x - chesssize * 0.5;
	int y = margin_y + chesssize * pos->y - chesssize * 0.5;
	int flag = changchessif;
	if (flag == 0) {
		if (kind == CHESS_WHITE)
		{
			//putimage(x, y, &whitechessImg);
			putimagePNG(x, y, &whitechessImg);
		}
		else
		{
			//putimage(x, y, &blackchessImg);
			putimagePNG(x, y, &blackchessImg);
		}

		updategameMap(pos);
	}
	if (flag == 1) {
		if (kind == CHESS_WHITE)
		{
			//putimage(x, y, &whitechessImg);
			putimagePNG(x, y, &blackchessImg);
		}
		else
		{
			//putimage(x, y, &blackchessImg);
			putimagePNG(x, y, &whitechessImg);
		}

		updategameMap(pos);
	}
	
	

}

//��ʼ����������
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradesize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chesssize = chessSize;
	

	for (int i = 0; i < gradeSize; i++)
	{
		vector<int>row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessmap.push_back(row);
	}
}


bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int row = (x - margin_x) / chesssize;
	int col = (y - margin_y) / chesssize;

	int leftTopPosX = margin_x + chesssize * row;
	int leftTopPosY = margin_y + chesssize * col;
	int offset = chesssize * 0.25; // 20 �������ģ����������

	int len;
	int selectPos = false;

	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->x = row;
			pos->y = col;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// �������Ͻǵľ���
		len = sqrt((x - leftTopPosX - chesssize) * (x - leftTopPosX - chesssize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->x = row+1;
			pos->y = col ;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chesssize) * (y - leftTopPosY - chesssize));
		if (len < offset) {
			pos->x = row;
			pos->y = col+1;
			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}

		// �������½ǵľ���
		len = sqrt((x - leftTopPosX - chesssize) * (x - leftTopPosX - chesssize) + (y - leftTopPosY - chesssize) * (y - leftTopPosY - chesssize));
		if (len < offset) {
			pos->x = row + 1;
			pos->y = col + 1;

			if (chessmap[pos->x][pos->y] == 0) {
				selectPos = true;
			}
			break;
		}
	} while (0);

	return selectPos;
}




int Chess::getGradeSize()
{
	return gradesize;
}

int Chess::getChessData(int row, int col)
{
	return chessmap[row][col];
}

int Chess::getChessData(ChessPos* pos)
{
	return chessmap[pos->x][pos->y];
}

bool Chess::checkOver()
{
	bool flag = 0;

	if (checkwin())
	{
		flag = 1;//��ֽ���
		if (playerFlag == false)
		{
			//ִ����ʤ
			//mciSendString("play res/win.mp3",0,0,0);
			loadimage(0, "box\\victory.jpg", 793, 300);
			outtextxy(CHESSMAP_WIDTH/2-50, PICTURE_HEIGHT - 150 - 35, "�����������");
		}
		if (playerFlag == 1)
		{
			//ִ����ʤ
			//mciSendString("play res/lose.mp3", 0, 0, 0);
			loadimage(0, "box\\defeat.jpg", 793, 300);
			outtextxy(CHESSMAP_WIDTH / 2 - 50, PICTURE_HEIGHT - 150 - 35, "�����������");

		}
		_getch();
	}
	
	return flag;
}

bool Chess::checkwin()
{
	//Ӯ��true������false
	int row = lastpos.x;
	int col = lastpos.y;
	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradesize &&
			chessmap[row][col - i] == chessmap[row][col - i + 1] &&
			chessmap[row][col - i] == chessmap[row][col - i + 2] &&
			chessmap[row][col - i] == chessmap[row][col - i + 3] &&
			chessmap[row][col - i] == chessmap[row][col - i + 4] &&
			chessmap[row][col - i] != 0)
			return true;
	}

	// ��ֱ����(��������4��)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradesize &&
			chessmap[row - i][col] == chessmap[row - i + 1][col] &&
			chessmap[row - i][col] == chessmap[row - i + 2][col] &&
			chessmap[row - i][col] == chessmap[row - i + 3][col] &&
			chessmap[row - i][col] == chessmap[row - i + 4][col] &&
			chessmap[row - i][col] != 0)
			return true;
	}

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradesize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradesize &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessmap[row + i][col - i] == chessmap[row + i - 1][col - i + 1] &&
			chessmap[row + i][col - i] == chessmap[row + i - 2][col - i + 2] &&
			chessmap[row + i][col - i] == chessmap[row + i - 3][col - i + 3] &&
			chessmap[row + i][col - i] == chessmap[row + i - 4][col - i + 4] &&
			chessmap[row + i][col - i] != 0)
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < gradesize &&
			col - i >= 0 &&
			col - i + 4 < gradesize &&
			chessmap[row - i][col - i] == chessmap[row - i + 1][col - i + 1] &&
			chessmap[row - i][col - i] == chessmap[row - i + 2][col - i + 2] &&
			chessmap[row - i][col - i] == chessmap[row - i + 3][col - i + 3] &&
			chessmap[row - i][col - i] == chessmap[row - i + 4][col - i + 4] &&
			chessmap[row - i][col - i] != 0)
			return true;
	}

	return false;

}




void Chess::changechess()
{
	init();
}

void Chess::gobackchess()
{
	if (gobacktimes > 0) {
		chessmap[backlist[0].x][backlist[0].y] = 0;
		int x = margin_x + chesssize * backlist[0].x - chesssize * 0.5;
		int y = margin_y + chesssize * backlist[0].y - chesssize * 0.5;
		putimagePNG(x, y, &smallmap);

		chessmap[backlist[1].x][backlist[1].y] = 0;
		x = margin_x + chesssize * backlist[1].x - chesssize * 0.5;
		y = margin_y + chesssize * backlist[1].y - chesssize * 0.5;
		putimagePNG(x, y, &smallmap);
		backlist.erase(backlist.begin() , backlist.begin() + 2);
		gobacktimes--;
	}
	else {
		fillrectangle(PICTURE_WIDTH + 50, PICTURE_HEIGHT - 250, CHESSMAP_WIDTH - 50, 300);
		outtextxy(PICTURE_WIDTH + 50 + 10, PICTURE_HEIGHT - 250 - 35, "����ʧ��");
	}

	
}

void Chess::faill()
{
	loadimage(0, "defeat.jpg", 793, 300);
	_getch();
	init();
}




void Chess::updategameMap(chesspos* pos)
{
	
	chessmap[pos->x][pos->y] = playerFlag ? 1:-1;
	playerFlag = !playerFlag;
	lastpos = *pos;

}



void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}

}
