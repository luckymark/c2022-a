#include "chess.h"
#include <stdio.h>
#include <memory.h>
void initchess(struct Chess* data)
{
	memset(data->ChessMap, 0, sizeof(data->ChessMap));
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));
	data->PlayTurn = 1;
}
