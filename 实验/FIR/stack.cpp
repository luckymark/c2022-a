#include "Stack.h"
#include "Basic.h"


int push_record(int x, int y) {
	int count = 0;
	if (0 <= gStack.top && gStack.top < 225) {
		gStack.top++;
		gStack.date[gStack.top].x = x;
		gStack.date[gStack.top].y = y;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				gStack.date[gStack.top].board[count] = gBoard[i][j] - 0 + '0';
				count++;
			}
		}
		return 1;
	}
	return 0;
}

int pop_withdraw(int* x, int* y) {
	int count = 0, flag = 0;
	if (gStack.top <= 0) {
		return 0;
	}
	else if (gStack.top < 2) {
		gStack.top = 0;
	}
	else if(gStack.top >= 2){
		gStack.top -= 2;
	}
	*x = gStack.date[gStack.top].x;
	*y = gStack.date[gStack.top].y;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			gBoard[i][j] = gStack.date[gStack.top].board[count] - '0';
			count++;
		}
	}
	return 1;
}