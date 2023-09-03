#pragma once

const float node_size = 50;
const int board_size = 25;
const int ifdown = node_size * 0.4;
const int margin =50;

struct chessdata {
	//0:�հ�  1������  -1������
	int chessmap[board_size][board_size];

	int scoremap[board_size][board_size];
};

void initchessdata(struct chessdata*data);
