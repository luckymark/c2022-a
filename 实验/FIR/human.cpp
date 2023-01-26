#include "Human.h"
#include "Basic.h"
#include "Stack.h"
#include <graphics.h>

#define LSTEP 40
#define BOARDSIZE 600
#define X_REGRET 400
#define Y_REGRET 615
#define W_REGRET 105
#define H_REGRET 55

IMAGE gBgp_withdraw;

int human(int* x, int* y) {
	MOUSEMSG m;
	m = GetMouseMsg();
	if (m.uMsg == WM_LBUTTONDOWN) {
		if (0 <= m.x && m.x <= BOARDSIZE && 0 <= m.y && m.y <= BOARDSIZE) {
			*x = correct(m.x);
			*y = correct(m.y);
			return 1;
		}
		else if (X_REGRET <= m.x && m.x <= X_REGRET + W_REGRET && Y_REGRET <= m.y && m.y <= Y_REGRET + H_REGRET) {
			withdraw();
			return 2;
		}
	}
	return 0;
}

void withdraw() {
	int x = 0, y = 0;
	loadimage(&gBgp_withdraw, _T("..\\resource\\background.png"));
	if (gStack.top == 1) {
		if (gPlayer == gPlayer2) {
			gPlayer = gPlayer1;
		}
		else {
			gPlayer = gPlayer2;
		}
		gPiece = BPIECE;
	}
	pop_withdraw(&x, &y);
	//�ػ����̼�ȫ������
	clearrectangle(0, 0, 600, 600);
	putimage(0, 0, &gBgp_withdraw);
	drawLine();
	drawPoint();
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (gBoard[i][j] != EMPTY) {
				drawPiece(i, j);
			}
		}
	}
	//������ʾ��������
	if (gStack.top > 0) {
		//�β�round=0���������õ�����last_x��last_y���ʶ���ȡֵ����
		highlight(x, y, 0, 0, 0);
	}
}