#include <stdio.h>
#include <stdlib.h>

void startUp();
void gameInstructions();
void menu(char c);
void gameMap();

char map[6][6] = { "######",
				"#o #  ",
				"# ## #",
				"#  # #",
				"##   #",
				"######"
};


int main() {
	startUp();//��Ϸ��������

	gameInstructions();//��Ϸ˵�� 

	//��ʾ�˵� 
	printf("   ->  ��ʼ��Ϸ\n");
	printf("       �˳���Ϸ\n");
	printf("��Enter������Ϸ\n");
	char choose1;
	choose1 = getch();
	menu(choose1);

	//������Ϸ��ͼ
	gameMap();

	//��ҽ��в���
	system("cls");
	int i, x, y, p, q, j;
	char ch;

	x = 1; y = 1; p = 1; q = 5;
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
		}
		printf("\n");
	}
	while (x != p || y != q) {
		ch = getch();

		if (ch == 's' || ch == 'S') {
			if (map[x + 1][y] != '#') {
				map[x][y] = ' ';
				x++;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'w' || ch == 'W') {
			if (map[x - 1][y] != '#') {
				map[x][y] = ' ';
				x--;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'a' || ch == 'A') {
			if (map[x][y - 1] != '#') {
				map[x][y] = ' ';
				y--;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		if (ch == 'd' || ch == 'D') {
			if (map[x][y + 1] != '#') {
				map[x][y] = ' ';
				y++;
				map[x][y] = 'o';
			}
			else {
				printf("\a");
			}
		}

		system("cls");
		for (i = 0; i < 6; ++i) {
			printf("        ");
			for (j = 0; j < 6; ++j) {
				printf("%c  ", map[i][j]);
			}
			printf("\n");
		}
	}
	system("cls");
	printf("You Win!\n");
	Sleep(3000);
	return 0;
}

void startUp() {
	int i;
	int circle = 2;
	for (i = 0; i < circle; ++i) {
		system("cls");
		printf("        ��Ϸ���ڼ���");
		Sleep(500);
		system("cls");
		printf("        ��Ϸ���ڼ���.");
		Sleep(500);
		system("cls");
		printf("        ��Ϸ���ڼ���..");
		Sleep(500);
		system("cls");
		printf("        ��Ϸ���ڼ���...");
		Sleep(500);
	}
	system("cls");
	printf("        ��Ϸ������ϣ�\n");
	Sleep(1000);
}

void gameInstructions() {
	printf("<---����������[W][S][A][D]--->\n");
	printf("<---�ֱ��Ӧ[��][��][��][��]--->\n");
	printf("<---ע��ʹ��Ӣ�����뷨--->\n");
	Sleep(1000);
}

void menu(char c) {
	system("cls");
	if (c == 'S' || c == 's') {
		printf("        ��Ϸ������ϣ�\n");
		printf("<---����������[W][S][A][D]--->\n");
		printf("<---�ֱ��Ӧ[��][��][��][��]--->\n");
		printf("       ��ʼ��Ϸ\n");
		printf("   ->  �˳���Ϸ\n");
		printf("������5s��ر�\n");
		int i = 0;
		for (i = 0; i < 5; ++i) {
			system("cls");
			printf("������ %ds��ر�\n", 5 - i);
			Sleep(1000);
		}
		exit(0);//�˳����� 
	}
	else {
		printf("        ��Ϸ������ϣ�\n");
		printf("<---����������[W][S][A][D]--->\n");
		printf("<---�ֱ��Ӧ[��][��][��][��]--->\n");
		printf("   ->  ��ʼ��Ϸ\n");
		printf("       �˳���Ϸ\n");
		printf("��Enter������Ϸ\n");

	}
}

void gameMap() {
	system("cls");
	printf("---���ڼ�����Ϸ��ͼ---\n");

	int i, j;
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
			Sleep(100);
		}
		printf("\n");
		Sleep(200);
	}

	system("cls");
	printf("---Part1---\n");
	for (i = 0; i < 6; ++i) {
		printf("        ");
		for (j = 0; j < 6; ++j) {
			printf("%c  ", map[i][j]);
		}
		printf("\n");
	}
}

