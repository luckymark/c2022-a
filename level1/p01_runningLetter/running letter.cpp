#include<stdio.h>
#include<stdlib.h>
#define SIZE 51
int main() {
FLAG01:
	int step = 0, path = 0;
	while (step < SIZE) {
		if (step == SIZE - 1) {
			goto FLAG;
		}system("cls");
		path = 1;
		while (path <= step) {
			printf(" ");
			path++;
		}printf("гд");
		step++;
	}FLAG:
	while (step > 0) {
		if (step == 1) {
			goto FLAG01;
		}system("cls");
		path = 1;
		while (step >= path) {
			printf(" ");
			path++;
		}step--;
		printf("гд");
	}return 0;
}