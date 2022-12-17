//
// Created by XuanCheng on 2022/12/13.
//

#ifndef PUSHBOX_INIT_H
#define PUSHBOX_INIT_H

#define CHANGE 48

extern int map[17][24];
extern short bpos[2];
extern short upos[2];
extern int score;

void MapLoad();
void MapInit();
void ConsoleCursorHiden();
void Init();
void clear(short x, short y);
void move(short x,short y);
void viewscore(short x, short y);
//void usermove();
void movewbox();
void movebox(short x,short y);
void savescore();

#endif //PUSHBOX_INIT_H
