/*功能要求：
1.规则：汉诺塔（又称河内塔）问题是源于印度一个古老传说的益智玩具。大梵天创造世界的时候做了三根金刚石柱子，在一根柱子上从下往上按照大小顺序摞着64片黄金圆盘。
大梵天命令婆罗门把圆盘从下面开始按大小顺序重新摆放在另一根柱子上。并且规定，在小圆盘上不能放大圆盘，在三根柱子之间一次只能移动一个圆盘。
2.要求：打印出移动的步骤，like this：
A->B
A->C
B->C
...*/
#include <stdio.h>
void move(char from, char pass, char to,int n);
int main() {
	int allnumber = 0;
	scanf_s("%d",&allnumber);
	move('A','B','C',allnumber);
	return 0;
}
//A->B,n-1
//max from A->C
//B->C,n-1
void move(char from, char pass, char to, int n) {
	if (n==1) {
		printf("%c->%c\n", from, to);
	}
	else {
		move(from, to, pass, n - 1);
		printf("%c->%c\n", from, to);
		move(pass, from, to, n - 1);
	}
}