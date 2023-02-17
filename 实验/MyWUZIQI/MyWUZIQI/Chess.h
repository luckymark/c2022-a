#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//����λ��
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};
//��������
typedef enum {
	CHESS_WHITE = -1,
     CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	bool checkWin();
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y,ChessPos* pos);
	void chessDown(ChessPos* pos, chess_kind_t kind);
	int getGradeSize();//��ȡ���̴�С��13.15.19��
	int getChessData(int row, int col);

	bool checkOver();//ʤ�����

private:
	IMAGE chessBlackImg;//С����
	IMAGE chessWhiteImg;//С����

	int gradeSize;//��ȡ���̴�С��13.15.19��
	int margin_x; //������߽�
	int margin_y; //�����ϱ߽�
	float chessSize;//���Ӵ�С
	//�������ӷֲ� 0-�� 1-�� -1-�� 
	//chessMap[3][5]��ʾ�������е�����,���ڴ洢���ݣ�������������
	vector<vector<int>>chessMap;

	//���ڸ�˭����
	bool playerFlag;//true-���� false-����

	void updateGameMap(ChessPos* pos);

	ChessPos lastPos; //�������λ��
};




