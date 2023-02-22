#include "Chesscontrol.h"


Chesscontrol::Chesscontrol(Chessman* chessman, AI* ai, Chess* chess)
{
	this->chessman = chessman;
	this->ai = ai;
	this->chess = chess;

	chessman->init(chess);//��ʼ���ж����ӵĶ���
	ai->init(chess);
}

//��ʼ�Ծ�
void Chesscontrol:: play()
{
	//����ǰ���̳�ʼ��
	chess->init();
	while (1)
	{

		
		if (chess->changchessif) {
			//ai����
			
			ai->move();
			if (chess->checkOver())
			{
				chess->init();
				continue;

			}
			//��ʿ����
			chessman->move();
			if (chess->checkOver())
			{
				chess->init();
				continue;

			}
			if (chess->changEchessif) {
				chess->init();
			}
		}
		else{
			//��ʿ����
			chessman->move();
			if (chess->checkOver())
			{
				chess->init();
				continue;

			}
			if (chess->changEchessif) {
				chess->init();
				continue;
			}

			//ai��
			ai->move();
			if (chess->checkOver())
			{
				chess->init();
				continue;

			}
		}
		

		
	}
}
