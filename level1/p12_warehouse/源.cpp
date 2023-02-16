#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;        
    int quantity;  
} Item;


Item* items;  
int numItems;  

void displayInventory();
void addInventory();
void removeInventory();
void saveInventory();
void loadInventory();

int main() {
    loadInventory();
    int choice;
    do {
        printf("��ѡ���ܣ�\n");
        printf("1. ��ʾ����б�\n");
        printf("2. ���\n");
        printf("3. ����\n");
        printf("4. �˳�����\n");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            displayInventory();
            break;
        case 2:
            addInventory();
            break;
        case 3:
            removeInventory();
            break;
        case 4:
            saveInventory();
            exit(0);
        default:
            printf("��Чѡ�����������롣\n");
        }
    } while (choice != 4);

    return 0;
}

void displayInventory() {
    printf("�ͺ�\t����\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d\t%d\n", items[i].id, items[i].quantity);
    }
}


void addInventory() {
    int id, quantity;
    printf("������Ҫ���Ļ����ͺź�������\n");
    scanf_s("%d %d", &id, &quantity);

    int index = -1;
    for (int i = 0; i < numItems; i++) {
        if (items[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        
        Item* newItems = (Item*)realloc(items, (numItems + 1) * sizeof(Item));
        if (newItems == NULL) {
            printf("�ڴ治�㣬�޷�������¼��\n");
            return;
        }
        items = newItems;
        items[numItems].id = id;
        items[numItems].quantity = quantity;
        numItems++;
    }
    else {
     
        items[index].quantity += quantity;
    }

    printf("���ɹ���\n");
}


void removeInventory() {
    int id, quantity;
    printf("������Ҫ����Ļ����ͺź�������\n");
    scanf_s("%d %d", &id, &quantity);

 
    int index = -1;
    for (int i = 0; i < numItems; i++) {
        if (items[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("���ﲻ���ڣ��޷����⡣\n");
    }
    else
    {
      
        if (items[index].quantity < quantity) {
            printf("��治�㣬�޷����⡣\n");
        }
        else {
           
            items[index].quantity -= quantity;
            printf("����ɹ���\n");
        }
    }
}


void saveInventory() {
    FILE* file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }for (int i = 0; i < numItems; i++) {
        fprintf(file, "%d %d\n", items[i].id, items[i].quantity);
    }

    fclose(file);
}
void loadInventory() {
    FILE* file = fopen("inventory.txt", "r");
    if (file == NULL) {
        
        items = NULL;
        numItems = 0;
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

 
    char* buffer = (char*)malloc(size);
    if (buffer == NULL) {
        printf("�ڴ治�㣬�޷���ȡ�ļ���\n");
        fclose(file);
        return;
    }
    fread(buffer, 1, size, file);
    fclose(file);

    int id, quantity;
    int numItems = 0;
    char* p = buffer;
    while (sscanf(p, "%d %d\n", &id, &quantity) == 2) {
        numItems++;
        p += 2;  
        while (*p >= '0' && *p <= '9') p++;  
    }

    Item* newItems = (Item*)malloc(numItems * sizeof(Item));
    if (newItems == NULL) {
        printf("�ڴ治�㣬�޷���ȡ�ļ���\n");
        free(buffer);
        return;
    }
    items = newItems;
    p = buffer;
    for (int i = 0; i < numItems; i++) {
        scanf_s(p, "%d %d\n", &id, &quantity);
        items[i].id = id;
        items[i].quantity = quantity;
        p += 2;  
        while (*p >= '0' && *p <= '9') p++; 

    free(buffer);
    numItems = numItems;
}