#include <stdio.h>
#include <stdlib.h>
void menu(int number);

void goods();

void popin();

void popout();

int line();

int main() {
    int num;
    while (1){
        printf("�˵�\n"
               "1.��ʾ����б�\n"
               "2.���\n"
               "3.����\n"
               "4.�˳�����\n");
        scanf("%d",&num);
        menu(num);
        system("pause");
        system("cls");
    }
    return 0;
}

void menu(int number){
    switch (number){
        case 1:
            goods();
            break;
        case 2:
            popin();
            break;
        case 3:
            popout();
            break;
        case 4:
            exit(0);
        default:
            printf("������˵��е�ѡ��");
            return;
    }
}

void popout() {
    int num,num2;
    printf("������Ҫ����ı�ţ�\n");
    gets(num);
    FILE *fp;
    fp=fopen("C:\\Users\\Lenovo\\c2022-a\\level1\\p12_warehouse\\as.csv","r");
    fseek(fp,2L,SEEK_SET);
    for (int i = 0; i < line()-1; ++i) {
        fscanf(fp,"%d",num2);
        fseek(fp,5L,SEEK_CUR);
        if(num2==num) {
            break;
        }
    }
}

void popin() {
    char chy[2];
    int data[3];
    printf("��������Ʒ���ƣ���Ʒ��λ����Ʒ�ͺţ���������������");
    for (int i = 0; i < 2; ++i) {
        gets(chy[i]);
    }
    for (int i = 0; i < 3; ++i) {
        gets(data[i]);
    }
    FILE *fp = NULL ;
    fp = fopen("C:\\Users\\Lenovo\\c2022-a\\level1\\p12_warehouse\\as.csv","w") ;
    fseek(fp,1L,SEEK_END);
    fprintf(fp,"%c\t%c\t%d\t%d\t%d\n",chy[0],chy[1],data[0],data[1],data[2]);
    fclose(fp);
}

void goods() {
    FILE *fp;
    int i,j ;
    float *da[6][line()];
    fp=fopen("C:\\Users\\Lenovo\\c2022-a\\level1\\p12_warehouse\\as.csv","r");
    if( fp == NULL ){
        printf("Fail to open file!\n");
        return;}
    fseek(fp, 5L, SEEK_SET);
    for(i = 0 ;i < 6 ; i++) {
        for (j = 0; j < line()-1; j++) {
            fscanf(fp, "%f", &da[i][j]);
            fseek(fp, 1L, SEEK_CUR);   /*fpָ��ӵ�ǰλ������ƶ�*/
        }
    }
    for(i = 0 ;i < line()-1 ; i++) {
        printf("%f\t%f\t%f\t%f\t%f\t\n", da[0][i],
               da[1][i], da[2][i], da[3][i], da[4][i]);
    }
}

int line() {
    FILE *fp;
    fp = fopen("C:\\Users\\Lenovo\\c2022-a\\level1\\p12_warehouse\\as.csv", "r");
    if (fp == NULL) {
        printf("Fail to open file!\n");
        }
        int i = 0, m;
        fseek(fp, 5L, SEEK_SET);
        while (i != 0) {
            fscanf(fp, "%f", &i);
            fseek(fp, 5L, SEEK_CUR);
            m++;
        }
        fclose(fp);
        return m;
    }