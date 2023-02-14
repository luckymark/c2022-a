#include"wuziqi.h"
void fillblank() {
	ab c;
	findbest(color, 2, c);
	draw_piece(best.x, best.y);
}

void findblank() {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			if (qp[j][i] != 0) {
				for (int a = -1; a < 2; a++)
				{
					for (int b = -1; b< 2; b++) {
						if ((j + a < len) && (i + b < len)) {
							if (xyvalue[j + a][i + b].flag != -1)
							{
								xyvalue[j + a][i + b].flag = 1;



							}
						}
					}

				}
			}

		}


	}
}