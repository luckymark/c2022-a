//
// Created by XuanCheng on 2022/12/15.
//

#ifndef WAREHOUSE_ACTIONS_H
#define WAREHOUSE_ACTIONS_H

typedef struct {
    char name[20];
    char type[10];
    double num;
}ware;

void menu();
void showware();
void addin();
void decrease();


#endif //WAREHOUSE_ACTIONS_H
