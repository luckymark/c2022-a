# define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#define NUM  100
#define PRODUCT_LEN  sizeof(struct ware) 
#define FORMAT "%-8d%-8s%-8d\n"
#define DATA  product[i].id,product[i].name,product[i].amount
int ShowProduct();
void ShowMenu();
void ModifyProduct();
void InputProduct();

typedef struct ware {
	int id;
	char name[20];
	int amount;
}ware;

ware product [NUM];

void ShowMenu()                        
{
	printf("\n\n\n\n\n");
	printf("\t\t|---------------------PRODUCT-------------------|\n");
	printf("\t\t|\t 1. input record                        |\n");
	printf("\t\t|\t 2. output record                       |\n");
	printf("\t\t|\t 3. modify record                       |\n");
	printf("\t\t|\t 4. show record                    |\n");
	printf("\t\t|\t 0. exit                                |\n");
	printf("\t\t|-----------------------------------------------|\n\n");
	printf("\t\t\tchoose(0-4):");
}

void InputProduct()                                    
{
	int i, iMax = 0;                                  
	char cDecide;                                    
	FILE* fp;                                          

	iMax = ShowProduct();

	if ((fp = fopen("product.txt", "ab")) == NULL)   
	{
		printf("can not open file\n");                
		return;
	}
	printf("press y/Y to input,or press any other to stop");
	getchar();                                       
	cDecide = getchar();                             
	while (cDecide == 'y' || cDecide == 'Y')        
	{
		printf("Id:");                             
		scanf("%d", &product[iMax].id);
		for (i = 0; i < iMax; i++)
			if (product[i].id == product[iMax].id)    
			{
				printf("the id is existing,press any key to continue!");
				_getch();
				fclose(fp);                  
				return;
			}
		printf("Name:");                           
		scanf("%s", &product[iMax].name);
		printf("Amount:");                           
		scanf("%d", &product[iMax].amount);

		if (fwrite(&product[iMax], PRODUCT_LEN, 1, fp) != 1)  
		{
			printf("can not save!\n");
			_getch();                                
		}
		else
		{
			printf("product Id %d is saved!\n", product[iMax].id);
			iMax++;
		}
		printf("press y/Y to continue input,or press any other to stop");      
		getchar();                                 
		cDecide = getchar();                        
	}
	fclose(fp);                                      
	printf("Input is over!\n");
}


void OutputProduct()                              
{
	FILE* fp;
	int id, i, iMax = 0, iOut = 0;             
	char cDecide;                                 

	iMax = ShowProduct();

	if (iMax <= -1)                                
	{
		printf("please input first!");
		return;
	}

	printf("please input the id:");
	scanf("%d", &id);                             
	for (i = 0; i < iMax; i++)
	{
		if (id == product[i].id)                   
		{
			printf("find the product,press y/Y to output:");
			getchar();
			cDecide = getchar();
			if (cDecide == 'y' || cDecide == 'Y')   
			{
				printf("input the amount to output:");
				scanf("%d", &iOut);
				product[i].amount = product[i].amount - iOut;
				if (product[i].amount < 0)          
				{
					printf("the amount is less than your input and the amount is 0 now!\n");
					product[i].amount = 0;          
				}
				if ((fp = fopen("product.txt", "rb+")) == NULL)     
				{
					printf("can not open file\n");  
					return;
				}
				fseek(fp, i * PRODUCT_LEN, 0);       
				if (fwrite(&product[i], PRODUCT_LEN, 1, fp) != 1) 
				{
					printf("can not save file!\n");
					_getch();
				}
				fclose(fp);
				printf("output successfully!\n");
				ShowProduct();                    
			}
			return;
		}
	}
	printf("can not find the product£¡\n");         
}


int ShowProduct()                              
{
	int i, iMax = 0;
	FILE* fp;
	if ((fp = fopen("product.txt", "rb")) == NULL)    
	{
		printf("can not open file\n");                
		return -1;
	}
	while (!feof(fp))                                 
		if (fread(&product[iMax], PRODUCT_LEN, 1, fp) == 1)
			iMax++;                                       
	fclose(fp);                                       

	if (iMax == 0)                                     
		printf("No record in file!\n");
	else                                               
	{
		printf("id     name     amount\n");
		for (i = 0; i < iMax; i++)
		{
			printf(FORMAT, DATA);                      
		}
	}
	return iMax;
}
	
void ModifyProduct()                           
{
	FILE* fp;
	int i, iMax = 0, id;

	iMax = ShowProduct();
	if (iMax <= -1)                              
	{
		printf("please input first!");
		return;
	}

	printf("please input the id to modify:");
	scanf("%d", &id);
	for (i = 0; i < iMax; i++)
	{
		if (id == product[i].id)               
		{
			printf("find the product, you can modify!\n");
			printf("id:");
			scanf("%d", &product[i].id);
			printf("Name:");
			scanf("%s", &product[i].name);
			printf("Amount:");
			scanf("%d", &product[i].amount);
			if ((fp = fopen("product.txt", "rb+")) == NULL)
			{
				printf("can not open\n");
				return;
			}
			fseek(fp, i * PRODUCT_LEN, 0);            
			if (fwrite(&product[i], PRODUCT_LEN, 1, fp) != 1)
			{
				printf("can not save!");
				_getch();
			}
			fclose(fp);
			printf("modify successful!\n");
			ShowProduct();                        
			return;
		}
	}
	printf("can not find information£¡\n");
}



int main()
{
	ShowMenu();
	int iItem;
	scanf("%d", &iItem);          
	while (iItem)
	{
		switch (iItem)
		{
		case 1:InputProduct(); break; 
		case 2:OutputProduct(); break; 
		case 3:ModifyProduct(); break; 
		case 4:ShowProduct(); break;
		default:printf("input wrong number");
		}
		_getch();                       
		ShowMenu();                    
		scanf("%d", &iItem);          
	}
}
