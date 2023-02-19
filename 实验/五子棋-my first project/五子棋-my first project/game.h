#pragma once
typedef enum
{
	Íæ¼Ò = 1,µçÄÔ
}player;
void playmusic(int musicchoice);
void closemusic(int musicchoice);
void changemusic(int musicchoice);
void Judge_victory(player Players, int playertype, int arr[15][15], int x, int y, int musicchoice);
void game(int number);
int caculateX(int X);
int caculateY(int Y);
void computerplay(int type,int X,int Y,int musicchoice);
void printred(int x, int y);
void clearredWhite(int x, int y);
void clearredBlack(int x, int y);