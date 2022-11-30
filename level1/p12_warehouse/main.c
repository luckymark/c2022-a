#define _CRT_SECURE_NO_WARNINGS
#define MAX 1000
#include<stdlib.h>
#include<stdio.h>
typedef struct data {
	int number;
	int no;
}data;

int in_list(int list[MAX], int len,int val) {
	int res = 0;
	for (int i = 0; i <= len; i++) {
		if (list[i] == val) res = 1;
	}
	return res;
}
void put() {
	FILE* fp = NULL;
	int no[MAX],count = 0;
	fp = fopen("data.txt", "r");
	data data;
	char name[100];
	if (check_null(fp,0) != 1) {
		while (!feof(fp)) {
			fscanf(fp, " %s %d %d", &name, &data.number, &data.no);
			no[count] = data.no;
			count += 1;
		}
	}

	fclose(fp);
	fp = fopen("data.txt","a");
	rewind(stdin);
	printf("plz input data's name.\n");
	gets(name);
	printf("plz input the count of %s.\n", name);
	rewind(stdin);
	scanf_s("%d", &data.number);
	printf("pls input the no. of %s.\n", name);
	rewind(stdin);
	scanf_s("%d", &data.no);
	while(in_list(no, count, data.no)) {
		printf("No.%d is already in list\n",data.no);
		printf("pls input the no. of %s.\n", name);
		scanf_s("%d", &data.no);
		rewind(stdin);
	}
	if (feof(fp) == 0) fprintf(fp, "\n");
	fprintf(fp, " %s %d %d", name, data.number, data.no);

	fclose(fp);
}

int check_null(FILE* fp,int opener) {
	char ch;
	int res;
	ch = fgetc(fp);
	if (ch == EOF) {
		res = 1;
		if(opener == 1) printf("THE LIST IS NULL NOW!!\n");
	}
	else res = 0;
	return res;
}

void show_list() {
	FILE* fp = NULL;
	fp = fopen("data.txt","r");
	data data;
	char name[100];
	if(check_null(fp,1) != 1){
		while (!feof(fp)) {
			fscanf(fp," %s %d %d", &name, &data.number, &data.no);
			printf("No.%10d %10s : %4d\n", data.no, name, data.number);
		}
	}

	fclose(fp);
}

char pop() {
	FILE* fp = NULL, * fp1 = NULL;
	data data;
	int no;
	char name[100];
	int count = 0, res = 0;
	fp = fopen("data.txt", "r");
	fp1 = fopen("temp.txt", "w");
	
	if (!check_null(fp,1)) {
		printf("plz input the data's .no that U want to pop.\n");
		scanf_s("%d", &no);
		rewind(stdin);

		while (!feof(fp)) {
			fscanf(fp, " %s %d %d", &name, &data.number, &data.no);
			if (data.no != no) {
				if (count != 0) fprintf(fp1, "\n");
				fprintf(fp1, " %s %d %d", name, data.number, data.no);
				count += 1;
			}
			else {
				res = 1;
				printf("%s is poped.\n", name);
			}
		}
		if (res == 0) printf("error\n");
		else {
			fclose(fp);
			fclose(fp1);
			fp = fopen("data.txt", "w");
			fp1 = fopen("temp.txt", "r");
			if (count > 0) {
				count = 0;
				while (!feof(fp1)) {
					fscanf(fp1, " %s %d %d", &name, &data.number, &data.no);
					if (count != 0) fprintf(fp, "\n");
					fprintf(fp, " %s %d %d", name, data.number, data.no);
					count++;
				}
			}
		}
	}
	
	fclose(fp);
	fclose(fp1);
}

int main() {
	int num,open = 1;
	while (open) {
		printf("1:put , 2: pop , 3:show the list , other key: exit\n");
		scanf_s("%d", &num);
		rewind(stdin);
		switch (num) {
		case 1:
			put();
			break;
		case 2:
			pop();
			break;
		case 3:
			show_list();
			break;
		default:
			open = 0;
			break;
		}
	}
	return 0;
}