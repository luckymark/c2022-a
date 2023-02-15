#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ļ����λ��
#define FILEPATH "F:\Program Files (x86)\Git\c2022-a\level1\p12_warehouse\data.txt"
#define MAXSIZE 1000// ��������С

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
        printf("�ļ���ʧ��\n");
        return;
    }
    char buf[MAXSIZE];
    strncpy_s(buf, MAXSIZE, "", MAXSIZE);
    int i = 0;
    while (fgets(buf, MAXSIZE, fp) != NULL) {
        size_t len = (size_t)strlen(buf) - 1;
        buf[len] = '\0';    // ɾ�����з�
        size = i / 3;
        // ��Ʒ����
        if (i % 3 == 0) {
            strncpy_s(gs[size].name, MAXSIZE, buf, len);
        }
        // ��Ʒ���
        else if (i % 3 == 1) {
            gs[size].stock = atoi(buf);
        }
        // ��Ʒ��λ
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
        printf("�ļ���ʧ��\n");
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
        printf("�� ��ʾ����б�\n");
        printf("�� ��        ��\n");
        printf("�� ��        ��\n");
        printf("�� �� �� ��  ��\n");
        printf("***************\n");
        printf("��������������ֽ��в���:");

        int opt, data1, data2;
        scanf_s("%d", &opt);

        if (opt == 1) {
            for (int i = 0; i < size; i++) {
                printf("%d.%s:%d%s\n", i + 1, gs[i].name, gs[i].stock, gs[i].unit);
            }
        }
        else if (opt == 2) {
            printf("�������Ʒǰ������:");
            scanf_s("%d", &data1);
            if (data1 < 1 || data1 > size) {
                printf("��������ڵ���ţ�1 - %d��", size);
                continue;
            }
            printf("�޸�ǰ�Ŀ��Ϊ:%d%s\n�������������:", gs[data1 - 1].stock, gs[data1 - 1].unit);
            scanf_s("%d", &data2);
            gs[data1 - 1].stock += data2;
            printf("������\n");
        }
        else if (opt == 3) {
            printf("�������Ʒǰ������:");
            scanf_s("%d", &data1);
            if (data1 < 1 || data1 > size) {
                printf("��������ڵ���ţ�1 - %d��", size);
                continue;
            }
            printf("�޸�ǰ�Ŀ��Ϊ:%d%s\n��������������:", gs[data1 - 1].stock, gs[data1 - 1].unit);
            scanf_s("%d", &data2);
            gs[data1 - 1].stock -= data2;
            printf("�������\n");
        }
        else if (opt == 4) {
            fresh_data();
            break;
        }
        else {
            printf("��������ȷ�����\n");
        }
    }

    return 0;
}
