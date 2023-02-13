#include "title.h"

MOUSEMSG msg;


int main(void)
{
	drawBoard();
	mciSendString(L"open AIMusic2_classic.mp3 alias m", NULL, 0, NULL);
	mciSendString(L"play m repeat", NULL, 0, NULL);           //播放音乐


	while (1)
	{
		msg = GetMouseMsg(); 
	
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN: 
			if ((msg.x >= 250) && (msg.x < 475) && (msg.y >= 125) && (msg.y <= 175)) 
			{
				playerVSplayer(); 
			}
			if ((msg.x >= 250) && (msg.x < 475) && (msg.y >= 195) && (msg.y <= 245)) 
			{
				playerVSAI(); 
			}
			if ((msg.x >= 250) && (msg.x < 475) && (msg.y >= 265) && (msg.y <= 315)) //在机机对战区域按下
			{
				AIVSAI(); 
			}
			
			break;
		}
	}
	return 0;
}
