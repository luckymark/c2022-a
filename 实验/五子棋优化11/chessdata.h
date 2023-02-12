#pragma once

const float node_size = 50;
const int board_size = 25;
const int ifdown = node_size * 0.4;
const int margin =50;

struct chessdata {
	//0:¿Õ°×  1£ººÚ×Ó  -1£º°××Ó
	int chessmap[board_size][board_size];

	int scoremap[board_size][board_size];
};

void initchessdata(struct chessdata*data);
