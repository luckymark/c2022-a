#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define alllength 100
#define turn 5
char* encode(char* passward)
{	
	char unwatch[alllength];
	char* un = unwatch;
	for (int i = 0; i < strlen(passward); i++)
	{
		unwatch[i] = passward[i] + i + i*i+turn;

	}
	unwatch[strlen(passward)] = '\n';
	return un;

}
char* decode(char* text)
{
	char again[alllength];
	char* aga = again;
	for (int i = 0; i < strlen(text); i++)
	{
		again[i] = * (encode(text)+i) - i - i * i - turn;
	}
	again[strlen(text)] = '\n';
	return aga;

}
int main()
{
	char pass[alllength];
	char* org = pass;
	scanf_s("%s", pass,20);
	for (int i = 0; i < strlen(pass); i++)
	{
		printf("%c", *(encode(org) + i));
	}
	printf("\n");
	for (int i = 0; i < strlen(pass); i++)
	{
		printf("%c", *(decode(org) + i));
	}
	return 0;
}