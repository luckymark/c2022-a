#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

#define CHESSMAP_WIDTH 800
#define CHESSMAP_HEIGHT 595
#define PICTURE_WIDTH 595
#define PICTURE_HEIGHT 595
#define background COLORREF RGB(222,192,164)
typedef struct ChessPos
{
	int x;
	int y;
	ChessPos(int r = 0, int c = 0) :x(r), y(c) {}
}chesspos;

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;


class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	//�洢��ǰ������ӷֲ�����
	vector<vector<int>> chessmap;
	
	void init();//��ʼ������
	
	bool clickBoard(int x, int y, ChessPos* pos);//�������Ƿ���Ч
	
	void chessDown(ChessPos* pos, chess_kind_t kind);//�������λ�ã���ʾ����

	int getGradeSize();//�˺�����ȡ���̴�Сo

	//��ȡָ��λ���Ǻ��廹�ǰ��廹�ǿհ�
	
	int getChessData(int row, int col);
	int getChessData(ChessPos *pos);
	
	bool checkOver();//�������Ƿ����
	bool checkwin();//�ж�ʤ��
	bool changchessif=false;//���ӵ��ж�ֵ
	bool changEchessif;//���ӵ��ж�ֵ,�Ƿ���
	int gobacktimes;
	void changechess();//����
	void gobackchess();//����
	void faill();//����
	vector <chesspos> backlist;

private :
	IMAGE blackchessImg;//����
	IMAGE whitechessImg;//����
	IMAGE smallmap;//������

	int gradesize;//���̴�С(13,15,17,19)
	int margin_x;//�������߽糤��
	int margin_y;//�����ϱ߽�߽糤��

	float chesssize;//���ӵĴ�С

	

	//��ʾ���巽������ɫ
	//0:��     1������    -1������
	bool playerFlag;
	
	//������������
	void updategameMap(chesspos* pos);

	//�ϸ����λ�ã��Ա�����ж������ͻ���
	chesspos lastpos;
};

