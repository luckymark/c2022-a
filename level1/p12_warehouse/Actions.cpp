//
// Created by XuanCheng on 2022/12/15.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Actions.h"


void menu() {
    int input;
    while(true) {
        printf("请输入您需要的功能对应的数字：\n");
        printf("1、显示存货列表\n"
               "2、入库\n"
               "3、出库\n"
               "4、退出程序\n");
        scanf("%d",&input);
        getchar();
        switch (input) {
            case 1:{
                showware();
                break;
            }
            case 2:{
                addin();
                break;
            }
            case 3:{
                decrease();
                break;
            }
            case 4:{
                return;
            }
            default:{
                printf("输入错误请重新输入\n");
            }
        }
    }
}

void decrease() {
    ware temp,cmp;
    FILE *fp1,*fp2;
    fp1 = fopen("ware.data", "r+b");
    fp2 = fopen("temp.data", "w+b");
    while (true) {
        cmp.num = 0;
        printf("请输入要出库的名称 类型 数量，以空格间隔 按Q Q Q结束");
        scanf("%s %s %lf", cmp.name, cmp.type, &cmp.num);
        getchar();
        if((cmp.name[0] == 'Q' || cmp.name[0] == 'q') && (cmp.type[0] == 'Q' ||cmp.type[0] == 'q') && cmp.num == 0){
            break;
        }
        while (true) {
            int k = fread(&temp, sizeof(ware), 1, fp1);
            if (k == 0) {
                break;
            }
            if (strcmp(temp.name, cmp.name) != 0 && strcmp(temp.type, cmp.type) != 0) {
                fwrite(&temp, sizeof(ware), 1, fp2);
            } else {
                if (cmp.num > temp.num) {
                    printf("输入错误，请重新输入\n");
                    fclose(fp2);
                    remove("temp.data");
                    break;
                } else if (cmp.num == temp.num) {
                    continue;
                } else if (cmp.num < temp.num) {
                    temp.num -= cmp.num;
                    fwrite(&temp, sizeof(ware), 1, fp2);
                } else{
                    fclose(fp1);
                    fclose(fp2);
                    remove("temp.data");
                    return;
                }
            }
        }
        fclose(fp1);
        fclose(fp2);
        remove("ware.data");
        rename("temp.data","ware.data");
    }
    fclose(fp1);
    fclose(fp2);
}

void addin() {
    FILE *fp;
    fp = fopen("ware.data", "a+b");
    while(true) {
        if (fp == nullptr) {
            printf("读取/创建数据文件失败\n");
            system("pause");
            system("cls");
            return;
        }
        ware temp;
        temp.num = 0;
        printf("请输入名称 类型 数量，以空格间隔 按Q Q Q结束");
        scanf("%s %s %lf", temp.name, temp.type, &temp.num);
        getchar();
        if ((temp.name[0] == 'Q' || temp.name[0] == 'q') && (temp.type[0] == 'Q' ||temp.type[0] == 'q') && temp.num == 0) {
            break;
        } else {
            fwrite(&temp,sizeof(ware),1,fp);
        }
    }
    fclose(fp);
}

void showware() {
    system("cls");
    ware temp[100];
    FILE *fp;
    int ch;
    fp = fopen("ware.data","rb");

    if(fp == nullptr){
        printf("无数据文件，请重试");
        printf("\n");
        system("pause");
        system("cls");
    } else{
        for (int i = 0; i < 100; ++i) {
            //fp = fopen("ware.data","rb");
            //fseek(fp,(long)sizeof(ware)*i,SEEK_SET);
            int k = fread(&temp[i], sizeof(ware),1,fp);
            if(k == 0){
                break;
            }
            printf("%s %s %f",temp[i].name,temp[i].type,temp[i].num);
            printf("\n");
        }
        printf("\n");
        system("pause");
        fclose(fp);
        system("cls");
    }
}
