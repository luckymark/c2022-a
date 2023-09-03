#include<cstdio>
#include<cstring>
#include "ChessData.h"


void init_chessData(struct ChessData* data)                 //�ṹ������ĵ�ַ
{
	if (data == NULL)                 //ȷ���ǿ�
	{
		return;
	}
	memset(data->Chessmap, 0, sizeof(data->Chessmap));      //��ֵ��
	memset(data->Scoremap, 0, sizeof(data->Scoremap));
	data->playSign = true;

}