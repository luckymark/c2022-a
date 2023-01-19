extern int gPiece;
extern int gBoard[15][15];
extern int gPlayer;
extern int gPlayer1;
extern int gPlayer2;

typedef struct {
	int x;
	int y;
	char board[225];
}STACKDATE;

typedef struct {
	int top;
	STACKDATE date[226];
}STACK_RECORD;

extern STACK_RECORD gStack;

int push_record(int x, int y);

int pop_withdraw(int* x, int* y);
