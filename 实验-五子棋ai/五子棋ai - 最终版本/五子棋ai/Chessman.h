#pragma once
#include"Chess.h"
class Chessman
{
public:
	void init(Chess *chess);
	void move();

private:
	Chess *chess;//加一个判断对象，通过该指针对落点是否有效进行判断
};

