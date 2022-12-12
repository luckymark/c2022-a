//
// Created by XuanCheng on 2022/12/4.
//

#ifndef MAZE_INIT_H
#define MAZE_INIT_H

extern const int map[17][24];


void MapInit();
void ConsoleCursorHiden();
void Init();
void clear(short x, short y);
void move(short x,short y);
void usermove();

#endif //MAZE_INIT_H
