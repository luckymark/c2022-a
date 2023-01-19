extern int gPiece;
extern int gBoard[15][15];
extern int gPlayer;
extern int gPlayer1;
extern int gPlayer2;

enum _PIECE { EMPTY, BPIECE, WPIECE };
extern enum _PIECE PIECE;

int menu();

void drawLine();	//ºáÏòÎªxÖá£¬×İÏòyÖá

void drawPoint();

void drawBoard();

int correct(int t);

void drawPiece(int x, int y);

void highlight(int x, int y, int last_x, int last_y, int round);

int endJudge(int x, int y);

void turnRound(int flag);

int end(int flag, int round);
