#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 文件存放位置
#define FILEPATH "F:\Program Files (x86)\Git\c2022-a\level1\p12_warehouse\data.txt"
#define MAXSIZE 1000// 缓冲区大小

typedef struct Goods {
    char name[MAXSIZE];
    int stock;
    char unit[MAXSIZE];
}Goods;

Goods gs[1000];
int size = 0;

void init_data() {

    FILE* fp;
    fopen_s(&fp, FILEPATH, "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    char buf[MAXSIZE];
    strncpy_s(buf, MAXSIZE, "", MAXSIZE);
    int i = 0;
    while (fgets(buf, MAXSIZE, fp) != NULL) {
        size_t len = (size_t)strlen(buf) - 1;
        buf[len] = '\0';    // 删除换行符
        size = i / 3;
        // 商品名称
        if (i % 3 == 0) {
            strncpy_s(gs[size].name, MAXSIZE, buf, len);
        }
        // 商品库存
        else if (i % 3 == 1) {
            gs[size].stock = atoi(buf);
        }
        // 商品单位
        else if (i % 3 == 2) {
            strncpy_s(gs[size].unit, MAXSIZE, buf, len);
        }
        i++;
    }
    size++;
    fclose(fp);
}

void fresh_data() {

    FILE* fp;
    fopen_s(&fp, FILEPATH, "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s\n%d\n%s\n", gs[i].name, gs[i].stock, gs[i].unit);
    }
}

int main(void)
{
    init_data();

    while (1) {
        printf("***************\n");
        printf("① 显示存货列表\n");
        printf("② 入        库\n");
        printf("③ 存        库\n");
        printf("④ 退 出 程  序\n");
        printf("***************\n");
        printf("请输入上面的数字进行操作:");

        int opt, data1, data2;
        scanf_s("%d", &opt);

        if (opt == 1) {
            for (int i = 0; i < size; i++) {
                printf("%d.%s:%d%s\n", i + 1, gs[i].name, gs[i].stock, gs[i].unit);
            }
        }
        else if (opt == 2) {
            printf("请输入货品前面的序号:");
            scanf_s("%d", &data1);
            if (data1 < 1 || data1 > size) {
                printf("请输入存在的序号（1 - %d）", size);
                continue;
            }
            printf("修改前的库存为:%d%s\n请输入入库数量:", gs[data1 - 1].stock, gs[data1 - 1].unit);
            scanf_s("%d", &data2);
            gs[data1 - 1].stock += data2;
            printf("入库完成\n");
        }
        else if (opt == 3) {
            printf("请输入货品前面的序号:");
            scanf_s("%d", &data1);
            if (data1 < 1 || data1 > size) {
                printf("请输入存在的序号（1 - %d）", size);
                continue;
            }
            printf("修改前的库存为:%d%s\n请输入出库库数量:", gs[data1 - 1].stock, gs[data1 - 1].unit);
            scanf_s("%d", &data2);
            gs[data1 - 1].stock -= data2;
            printf("出库完成\n");
        }
        else if (opt == 4) {
            fresh_data();
            break;
        }
        else {
            printf("请输入正确的序号\n");
        }
    }

    return 0;
}
