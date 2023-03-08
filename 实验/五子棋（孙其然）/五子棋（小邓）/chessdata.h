//Chessdata.h
#pragma once
const int Block_size = 43;//���Ӵ�С
const int Board_width = 17;//������Ŀ
const int Dim = Block_size * 0.4;//ģ������

struct ChessData {
	//0:�հ�  1������  -1������
	int chessMap[Board_width][Board_width];
	//AI����������Ӽ�ֵ
	int scoreMap[Board_width][Board_width];
	//true:�ֵ��ڷ�����   false���ֵ������£�AI��
	bool playerFlag;
};

typedef struct point {
	int row;
	int  list;
}point_t;

void initChessData(struct ChessData*);