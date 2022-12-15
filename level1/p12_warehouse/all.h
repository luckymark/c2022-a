#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>


typedef struct
{
	char name[10];
	int member;
	int amount;
}Goods;

Goods goods[20];



void manu();

void show();

void in();

void out();

void sh();

void readout(const char* filename);

void writein(const char* filename);