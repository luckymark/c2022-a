#pragma once
#include"Chess.h"
class Chessman
{
public:
	void init(Chess *chess);
	void move();

private:
	Chess *chess;//��һ���ж϶���ͨ����ָ�������Ƿ���Ч�����ж�
};

