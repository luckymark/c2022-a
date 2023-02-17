#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	char modelNum[15];
	int num;
}Goods;
typedef struct _Node {
	Goods date;
	_Node* next;
}Node;
typedef struct {
	Node* head;
	Node* tail;
}List;
char title[100] = { 0 };

void readDate(List* list);
int searchNode(Node** p, char target[]);
void saveDate(List list);

void menu();
void inventoryList(List list);
void inWarehouse(List* list);
void exWarehouse(List* list);

int main() {
	char command;
	List list;
	list.head = list.tail = NULL;
	readDate(&list);
	do {
		menu();
		command = _getch();
		switch (command) {
		case '1':
			system("cls");
			inventoryList(list);
			break;
		case '2':
			system("cls");
			inWarehouse(&list);
			break;
		case '3':
			system("cls");
			exWarehouse(&list);
			break;
		case '4':
			break;
		default:
			break;
		}
		system("cls");
	} while (command != '4');
	saveDate(list);
	return 0;
}

void menu() {
	printf("\t\t\t\t##########�˵�###########\n");
	printf("\t\t\t\t#      1-��ʾ����б�   #\n");
	printf("\t\t\t\t#      2-���           #\n");
	printf("\t\t\t\t#      3-����           #\n");
	printf("\t\t\t\t#      4-�˳�����       #\n");
	printf("\t\t\t\t#########################\n");
}

void readDate(List* list) {
	FILE* fp;
	Goods good;
	fopen_s(&fp, "warehouse.txt", "r");
	if (fp) {
		fgets(title, 100, fp);
		do {
			fscanf_s(fp, "%s", good.modelNum, 15);
			fscanf_s(fp, "%d", &good.num);
			Node* node = (Node*)malloc(sizeof(Node));
			if (node) {
				node->date = good;
				node->next = NULL;
			}
			if (list->tail) {
				while ((list->tail)->next) {
					list->tail = (list->tail)->next;
				}
				(list->tail)->next = node;
			}
			else {
				list->head = node;
				list->tail = node;
			}
		} while (!feof(fp));
		fclose(fp);
	}
}

int searchNode(Node** p, char target[]) {
	int flag = 0;
	while (*p) {
		if (strcmp((*p)->date.modelNum, target) == 0) {
			flag = 1;
			break;
		}
		*p = (*p)->next;
	}
	return flag;
}

void inventoryList(List list) {
	char command;
	do {
		printf("\t#####��B�������˵�#####\n\n");
		printf("\t%s", title);
		Node* p = list.head;
		while (p) {
			printf("\t%s\t", p->date.modelNum);
			printf("\t%d\n", p->date.num);
			p = p->next;
		}
		command = _getch();
		system("cls");
	} while (command != 'b' && command != 'B');
}

void inWarehouse(List* list) {
	char command;
	Goods good;
	printf("###          �밴��������룬��B��ȡ�����          ###\n");
	command = _getch();
	system("cls");
	while (command != 'b' && command != 'B') {
		printf("###�����������������ͺš�������ENTER�Խ���һ��¼��###\n");
		printf("###   ������ɺ�B�����ز˵���������������������   ###\n");
		scanf_s("%s", good.modelNum, 15);
		scanf_s("%d", &good.num);
		Node* p = list->head;
		if (searchNode(&p, good.modelNum)) {
			p->date.num += good.num;
		}
		else {
			Node* node = (Node*)malloc(sizeof(Node));
			if (node) {
				strcpy_s(node->date.modelNum, strlen(good.modelNum) + 1, good.modelNum);
				node->date.num = good.num;
				node->next = NULL;
			}
			if (list->tail) {
				while ((list->tail)->next) {
					list->tail = (list->tail)->next;
				}
				(list->tail)->next = node;
			}
			else {
				list->head = node;
				list->tail = node;
			}
		}
		command = _getch();
		system("cls");
	}
}

void exWarehouse(List* list) {
	char command;
	Goods good;
	printf("###          �밴��������룬��B��ȡ������          ###\n");
	command = _getch();
	system("cls");
	while (command != 'b' && command != 'B') {
		printf("###�����������������ͺš�������ENTER�Խ���һ��¼��###\n");
		printf("###   ������ɺ�B�����ز˵���������������������   ###\n");
		scanf_s("%s", good.modelNum, 15);
		scanf_s("%d", &good.num);
		Node* p = list->head;
		if (searchNode(&p, good.modelNum)) {
			if (p->date.num < good.num) {
				printf("ERROR�������������ڿ���������밴��B�����������������\n");
			}
			else if (p->date.num > good.num) {
				p->date.num -= good.num;
			}
			else {
				//������������������ͬ��ɾ���û��������
				Node* dummy = (Node*)malloc(sizeof(Node));
				dummy->next = list->head;
				Node* pre = dummy;
				Node* cur = pre;
				while (cur != p) {
					pre = cur;
					cur = cur->next;
				}
				if (cur->next != NULL) {
					pre->next = cur->next;
					free(cur);
				}
				else {
					list->tail = pre;
					free(cur);
				}
				list->head = dummy->next;
				free(dummy);
			}
		}
		else {
			printf("ERROR������в����ڸ��ͺŻ���밴��B�����������������\n");
		}
		command = _getch();
		system("cls");
	}
}

void saveDate(List list) {
	FILE* fp;
	Goods good;
	fopen_s(&fp, "warehouse.txt", "w");
	fputs(title, fp);
	if (fp) {
		Node* p = list.head;
		while (p->next) {
			fputs(p->date.modelNum, fp);
			fprintf(fp, "  %d\n", p->date.num);
			p = p->next;
		}
		fputs(p->date.modelNum, fp);
		fprintf(fp, "  %d", p->date.num);
		fclose(fp);
	}
}