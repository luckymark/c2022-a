/*题目：简单进销存
功能要求：
1.实现如下的菜单（按数字选择菜单功能）：
- 显示存货列表
- 入库
- 出库
- 退出程序
1. 实现菜单对应功能（需记录货物的型号、数量等信息）；
1. 程序启动时从文件中读取当前库存数据，退出时保存库存数据；*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

const int STRNUM = 20;

int main() {
	/*
	1:显示存货列表
	2:入库
	3:出库
	4:退出
	*/
	int location = 0;
	int amount = 0;
	//0表示菜单，1表示存货列表（也就是货物都有哪些），2表示入库操作界面，3表示修改货物信息，4表示出库操作界面
	FILE* file;
	FILE* fileTemp;
	int tempNum=0;
	int ret;
	char c;
	char* q;
	char str[STRNUM] = { {} };
	int count=0;
	int delNum = 0;
	int* p;
	errno_t err1 = fopen_s(&file,"wareHouse.txt", "r+");
	errno_t err2;
	if (file==NULL) {
		printf("no file\n");
	}
	else {
		do {system("cls");
			switch (location) {
			case 0:
				printf("0:show item\n");
				printf("1:input item\n");
				printf("2:output item\n");
				//printf("3:change item\n");
				printf("4:exit\n");
				printf("please input number\n");
				c = _getch();
				switch (c) {
				case '0':
					location = 1;
					break;
				case '1':
					location = 2;
					break;
				case '2':
					location = 4;
					break;
				/*case '3':
					changeItem();
					break;*/
				case '4':
					goto end;
					break;
				default:
					printf("default:input again\n");
					printf("press any button to continue\n");
					c = _getch();
					break;
				}
				break;
			case 1:
				system("cls");
				fseek(file, 0, 0);
				count = 0;
				while (fgetc(file) != EOF) {
					fseek(file, -1, 1);
					printf("%d:", ++count);
					for (int i = 0; i < STRNUM; ++i) {
						putchar(fgetc(file));
					}
					fseek(file, STRNUM + 4, 1);
					printf("\n");
				}
				printf("%d:back\n", ++count);
				printf("choose number to see\n");
				scanf_s("%d",&tempNum);
				system("cls");
				if((tempNum < count) && (tempNum > 0)){
					fseek(file, (tempNum - 1) * (2*STRNUM + 4), 0);
					for (int i = 0; i < 2 * STRNUM ; ++i) {
						putchar(fgetc(file));
					}
					for (int i = 0; i < 4;++i) {
						str[i]=(fgetc(file));
					}
					p = (int*)str;
					printf("%d\n",*p);
					printf("\npress any button to back to menu\n");
					c = _getch();
					location = 0;
				}
				else if (tempNum == count) {
					location = 0;
				}
				else {
					printf("reinput the number\n");
					system("pause");
				}
				break;
			case 2:
				system("cls");
				printf("please input name of item\n");
				amount = 0;
				//输入Name
				fseek(file, 0, 2);
				printf("no more than %d alphabets\n", STRNUM - 2);
				scanf_s("%s", &str, STRNUM);
				for (int i = 1; i < STRNUM; ++i) {
					if (str[i-1]=='\0') {
						str[i-1] = ' ';
						str[i] = '\0';
					}
				}
				fwrite(str, sizeof(char), 20, file);
				//输入Type
				fseek(file, 0, 2);
				printf("input type\n");
				scanf_s("%s", &str, STRNUM - 2);
				for (int i = 1; i < STRNUM; ++i) {
					if (str[i - 1] == '\0') {
						str[i - 1] = ' ';
						str[i] = '\0';
					}
				}
				fwrite(str, sizeof(char), 20, file);
				//输入Amount
				//将amount的数量转换为字符串并且存入文件
				fseek(file, 0, 2);
				printf("input amount\n");
				scanf_s("%d", &amount);
				q = (char*)&amount;
				for (int i = 0; i < 4;++i) {
					str[i] = *q;
					fputc(str[i],file);
					q++;
				}
				printf("press any button to back to menu\n");
				c = _getch();
				location = 0;
				break;
				/*case 3:
					break;*/
			case 4:
				count = 0;
				delNum = 0;
				err2 = fopen_s(&fileTemp, "temp.txt", "w+");
				fseek(file,0,0);
				while (fgetc(file)!=EOF) {
					printf("%d:", ++count);
					fseek(file, -1, 1); 
					for (int i = 0; i < STRNUM ;++i) {
						putchar(fgetc(file));
					}
					fseek(file,STRNUM+4,1);
					printf("\n");
				}
				scanf_s("%d", &delNum);
				if (delNum > count) {
					//nothing happen
					fclose(fileTemp);
				}
				else {
					fseek(file, 0, 0);
					fseek(fileTemp,0,0);
					for (delNum; delNum > 1; --delNum) {
						for (int i = 0; i < STRNUM * 2 + 4;++i) {
							fputc(fgetc(file), fileTemp);
						}
					}
					fseek(file,2*STRNUM+4,1);
					fseek(fileTemp,0,1);
					while (fgetc(file) != EOF) {
						fseek(file,-1,1);
						fputc(fgetc(file), fileTemp);
					}
					fclose(fileTemp);
					printf("press any button to back\n");
					c = _getch();
					location = 0;
					fclose(file);
					ret = remove("wareHouse.txt");
					if (ret == 0)
					{
					}
					else
					{
						printf("error\n");
					}
					char oldname[] = "temp.txt";
					char newname[] = "wareHouse.txt";
					ret = rename(oldname, newname);
					if (ret == 0)
					{
					}
					else
					{
						printf("error\n");
					}
					fopen_s(&file, "wareHouse.txt", "r+");
				}
				break;
			default:
				printf("input again\n");
				printf("press any button to continue\n");
				c = _getch();
				break;
				}while (0);
			} while (1);
	}
	end:
	//fwrite(STR1,sizeof(STR1),1,file);
		fclose(file);
		printf("you have closed\n");
	return 0;
}