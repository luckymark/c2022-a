extern int gPiece;
extern int gBoard[15][15];
extern int gPlayer;
extern int gPlayer1;
extern int gPlayer2;

//enum direction { U, RU, R, RD, D, LD, L, LU };

typedef struct {
	int x;
	int y;
}Direction;

int getScore(int** vBoard, int player);

int evaluate(int** vBoard);

void findBoundary(int boundary[], int** vBoard);

int maxminSearch(int depth, int player, int** vBoard, int alpha, int beta);

int AI(int* x, int* y, int round);

int Max(int a, int b);

int Min(int a, int b);

void swap(int* a, int* b);

void secondRound(int* x, int* y);
