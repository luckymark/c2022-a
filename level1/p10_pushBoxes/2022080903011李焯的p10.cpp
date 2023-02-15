#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

int screen[9][11];
int  x= 4;
int y = 5;
int cum();
void printMap();
bool isWin();
bool isLose();
int getMap(FILE* fp,int level);
typedef void (*fp)();     //��ǿ�Է���ֵΪ����ָ��ĺ����Ŀɶ��ԣ�typedef����ָ�룻
void movew();
void moves();
void movea();
void moved();
fp move(char ch);

void Beg()
{
	system("cls");
	printf("��ʼ��Ϸ�밴1\n�˳���Ϸ�����\n");
}

int main() {
	int level = 1;
	int steps = 0;
	char ch,begin,end;
	Beg();
	begin = _getch();
	if (begin == '1') 
	{
		printf("����wsad/WSAD��������������������Ϸ\n");
		while (1) 
		{
			system("cls");
			FILE* fp = NULL;
			getMap(fp, level);
			printMap();
			ch = _getch();
			void (*p)();
			p = move(ch);
			p();
			steps++;
			if (isLose())
			{
				system("cls");
				printMap();
				printf("��Ϸʧ��");
				return 0;
			}
			if (isWin())		
			{
				if (level == 3) {
					printf("��ϲ��ͨ������Ϸ!");
					FILE* fpp;
					fpp = fopen("result", "w");
					fprintf(fpp, "%d", steps);
					fclose(fpp);
					return 0;
				}
				level++;

			}
		}
	}
	else
		return 0;
}
void movew() {
	if (x > 0) {
		if (screen[x - 1][y] == 1) {
			return;/*������ӵ�������ǽ�����ͼ���ᷢ���仯����Ϊ
			�Ʋ�����*/
		}
		else if (screen[x - 1][y] == 0) {
			screen[x - 1][y] += 3;
			screen[x][y] -= 3;
			x--;/*���ǰ���ǿյأ�����Ҫ��ǰ�ƶ�һ��Ҳ����ԭ���˵�λ��
			��ɿյأ�ǰ���Ŀյر���ˣ��յأ�0������ˣ�3����Ҫ��3��
			�˱�ɿյ���Ҫ��3*/
		}
		else if (screen[x - 1][y] == 4) {
			screen[x - 1][y] += 3;
			screen[x][y] -= 3;
			x--;
		}//һ����
		else if (screen[x - 1][y] == 2 || screen[x - 1][y] == 6) {
			if (screen[x - 2][y] == 0) {
				screen[x - 2][y] += 2;//����ǰ��ĸ������ӣ�2��
				screen[x - 1][y] += 1;//���ӵ�λ�ñ���ˣ�3��
				screen[x][y] -= 3;/*���ǰ���ǿյأ�����Ҫ��ǰ�ƶ�
				һ��Ҳ����ԭ�������ӵĸ��ӱ���ˣ��˵�λ�ñ�ɿ�
				�أ�ԭ�ȵĿյر������,���ӣ�2������ˣ�3����Ҫ��
				3���յر����*/
				x--;
			}
			else if (screen[x - 2][y] == 1) {
				return;
			}
			else if (screen[x - 2][y] == 2) {
				return;//������ӵ�ǰ����ǽ�������������ӣ��������Ʋ���
			}
			else if (screen[x - 2][y] == 4) {
				screen[x - 2][y] += 2;
				screen[x - 1][y] += 1;
				screen[x][y] -= 3;
				x--;
			}//��������©��
		}
	}
}
void moves() {
	if (x < 9) {
		if (screen[x + 1][y] == 1) {
			return;
		}
		else if (screen[x + 1][y] == 0) {
			screen[x + 1][y] += 3;
			screen[x][y] -= 3;
			x++;
		}
		else if (screen[x + 1][y] == 4) {
			screen[x + 1][y] += 3;
			screen[x][y] -= 3;
			x++;
		}
		else if (screen[x + 1][y] == 2 || screen[x + 1][y] == 6) {
			if (screen[x + 2][y] == 1) {
				return;
			}
			else if (screen[x + 2][y] == 0) {
				screen[x + 2][y] += 2;
				screen[x + 1][y] += 1;
				screen[x][y] -= 3;
				x++;
			}
			else if (screen[x + 2][y] == 2) {
				return;
			}
			else if (screen[x + 2][y] == 4) {
				screen[x + 2][y] += 2;
				screen[x + 1][y] += 1;
				screen[x][y] -= 3;
				x++;
			}
		}
	}
}
void movea() {
	if (y > 0) {
		if (screen[x][y - 1] == 1) {
			return;
		}
		else if (screen[x][y - 1] == 4) {
			screen[x][y - 1] += 3;
			screen[x][y] -= 3;
			y--;
		}
		else if (screen[x][y - 1] == 0) {
			screen[x][y - 1] += 3;
			screen[x][y] -= 3;
			y--;
		}
		else if (screen[x][y - 1] == 2 || screen[x][y - 1] == 6) {
			if (screen[x][y - 2] == 0) {
				screen[x][y - 2] += 2;
				screen[x][y - 1] += 1;
				screen[x][y] -= 3;
				y--;
			}
			else if (screen[x][y - 2] == 1) {
				return;
			}
			else if (screen[x][y - 2] == 2) {
				return;
			}
			else if (screen[x][y - 2] = 4) {
				screen[x][y - 2] += 2;
				screen[x][y - 1] += 1;
				screen[x][y] -= 3;
				y--;
			}
		}
	}
}
void moved() {
	if (y < 9) {
		if (screen[x][y + 1] == 1) {
			return;
		}
		else if (screen[x][y + 1] == 4) {
			screen[x][y + 1] += 3;
			screen[x][y] -= 3;
			y++;
		}
		else if (screen[x][y + 1] == 0) {
			screen[x][y + 1] += 3;
			screen[x][y] -= 3;
			y++;
		}
		else
			if (screen[x][y + 1] == 2 || screen[x][y + 1] == 6) {
				if (screen[x][y + 2] == 0) {
					screen[x][y + 2] += 2;
					screen[x][y + 1] += 1;
					screen[x][y] -= 3;
					y++;
				}
				else if (screen[x][y + 2] == 4) {
					screen[x][y + 2] += 2;
					screen[x][y + 1] += 1;
					screen[x][y] -= 3;
					y++;
				}
				else if (screen[x][y + 2] == 2) {
					return;
				}
				else if (screen[x][y + 2] == 1) {
					return;
				}
			}

	}
}
fp move(char ch)
{
	switch (ch)
	{
	case 'W':
	case'w':
		return movew;
	case 'S':
	case's':
		return moves;
	case 'A':
	case'a':
		return movea;
	case 'D':
	case'd':
		return moved;
	default:
		break;
	}
}
void printMap() {
	int i, j;
	printf("����wsad��������������������Ϸ\n");
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			switch (screen[i][j]) {
			case 0:
				printf("  ");//�� 
				break;
			case 1:
				printf("��");//ǽ 
				break;
			case 2:
				printf("��");//���� 
				break;
			case 3:
				printf("��");//�� 
				break;
			case 4:
				printf("��");//�յ� 
				break;
			case 6:
				printf("��");//���Ӻ��յ�
				break;
			case 7:
				printf("��");//�յ���ʾ��
				break;
			}
		}
		printf("\n");
	}
}
int cum() {
	int i, j, dterminal = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (screen[i][j] == 2) {
				dterminal++;
			}
		}
	}
	return dterminal;
} // �����յ����
bool isLose() {
	int i, j;
	int k = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (i > 0 && j > 0) {
				if (screen[i][j] == 2 || screen[i][j] == 6) {
					if (((screen[i - 1][j] == 1 || screen[i - 1][j] == 2 || screen[i - 1][j] == 6) && (screen[i][j - 1] == 1 || screen[i][j - 1] == 2 || screen[i][j - 1] == 6))
						|| ((screen[i][j - 1] == 1 || screen[i][j - 1] == 2 || screen[i][j - 1] == 6) && (screen[i + 1][j] == 1 || screen[i + 1][j] == 2 || screen[i + 1][j] == 6))
						|| ((screen[i + 1][j] == 1 || screen[i + 1][j] == 2 || screen[i + 1][j] == 6) && (screen[i][j + 1] == 1 || screen[i][j + 1] == 2 || screen[i][j + 1] == 6))
						|| ((screen[i][j + 1] == 1 || screen[i][j + 1] == 2 || screen[i][j + 1] == 6) && (screen[i - 1][j] == 1 || screen[i - 1][j] == 2 || screen[i - 1][j] == 6))) {
						k++;
					}
				} //�������ܲ����ٽ�����Ϸ�ˣ�
			}
		}
	}
	if (k ==cum()) {
		return true;
	}
	else
		return false;
}
bool isWin() {
	int i, j, k = 0;
	int t = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 11; j++) {
			if (screen[i][j] == 6) {
				k++;
			}
		}
	}
	if (k == cum()) {
		return true;
	}
	else
		return false;
} 
int getMap(FILE* fp ,int level)
{
	
	switch (level)
	{
	case 1:
		fp = fopen("map1.txt", "r");
		break;
	case 2:
		fp= fopen("map2.txt", "r");
		break;
	case 3:
		fp = fopen("map3.txt", "r");
		break;
	default:
		break;
	}
	if (fp == NULL) {
			printf("open error/n");
			return -1;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 11; j++) {
				fscanf(fp, "%d", screen[i][j]);
			}
		}
	fclose(fp);
	return 0;
}


