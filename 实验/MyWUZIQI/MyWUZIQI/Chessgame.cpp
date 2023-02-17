#include "Chessgame.h"
Chessgame::Chessgame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;


	man->init(chess);  //��ʼ������
	ai->init(chess);
}
	//�Ծֿ�ʼ
void Chessgame::play()
{
	chess->init();
	while (1)
	{//��������
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;

		}
		//AI latter
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;


		}
	}
}