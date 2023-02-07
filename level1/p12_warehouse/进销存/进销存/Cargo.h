#pragma once
typedef enum {
	large = 1, middle, small
}Type;
//货物类型
typedef struct cargonode {
	int price;
	int quantity;
	Type type;
	struct cargonode* Pnext;
}CargoNode;
//货物节点

void altercargo(CargoNode* p, int number,CargoNode*information, char* alter);
void delcargo(CargoNode* p, int number);
void addcargo(CargoNode* p, int price, int quantity, Type type);
CargoNode* MakeExistChain();
CargoNode* CreateLinkChain(int number);
char* change(Type type);