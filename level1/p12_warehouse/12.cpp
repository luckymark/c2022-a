#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct good{
	int total_number=0;
	int number;
	char form[128];
	char warename[128];
	struct good* next;
};
void addnode(struct good* list){
	struct good* temp=(struct good*)malloc(sizeof(struct good));
	temp->next=list->next;
	temp->number=0;
	list->next=temp;
	return;
}
void newWare(FILE** newware,char* name){
	int namelenth=strlen(name);
	char* nameform=(char*)malloc((namelenth+7)*sizeof(char));
	strcpy(nameform, name);
	strcat(nameform, ".txt");
	*newware = fopen(nameform,"r");
	if(*newware){//重名监测，"r"模式如果目录下没有该文件名的文件，文件流会保持为NULL
		printf("已有同名文件。\n\n");
		fclose(*newware);
		free(nameform);
		printf("选择功能（请输入对应编号）：\n");
		printf("1:新建仓库\n");
		printf("2:打开仓库\n");
		printf("0:结束程序\n");
		return;
	}else{
		fclose(*newware);
		*newware=fopen(nameform,"w");
		if(ferror(*newware)){
			printf("创建文件错误。\n\n");
		}else{
			rewind(*newware);
			fprintf(*newware,"%s 0\n",name);
			printf("成功创建仓库文件%s\n\n",nameform);
		}
		fclose(*newware);
		*newware=NULL;
	}
	printf("选择功能（请输入对应编号）：\n");
	printf("1:新建仓库\n");
	printf("2:打开仓库\n");
	printf("0:结束程序\n");
	free(nameform);
	return;
}
void linkList(FILE* nowware, struct good* list){
	fseek(nowware,0,SEEK_SET);
	fscanf(nowware,"%*s%d\n",&(list->total_number));
	int cnt=list->total_number;
	addnode(list);
	for(int i=0;i<cnt;i++){
		fscanf(nowware,"%s%d\n",(list->next->form),&(list->next->number));
		addnode(list);
	}
	return;	
}
void openWare(FILE** nowware,struct good* list,char* name){
	int namelenth=strlen(name);
	char* nameform=(char*)malloc((namelenth+7)*sizeof(char));
	strcpy(nameform, name);
	strcat(nameform, ".txt");
	*nowware = fopen(nameform,"r");
	if(!*nowware){
		printf("无该仓库文件。\n");
		fclose(*nowware);
		free(nameform);
		return;
	}else{
		fclose(*nowware);
		*nowware=fopen(nameform,"rt+");
		if(ferror(*nowware)){
			printf("打开文件错误。\n");
		}else{
			linkList(*nowware,list);
			strcpy(list->warename,name);
			printf("成功打开仓库文件%s\n\n",nameform);
			printf("选择功能（请输入对应编号）：\n");
			printf("3:关闭仓库\n");
			printf("4:从当前仓库入库\n");
			printf("5:从当前仓库出库\n");
			printf("6:显示当前仓库列表\n");
			printf("0:结束程序\n");
		}
	}
	free(nameform);
	return;
}
void deleteList(struct good* list){
	for(struct good* chase=list->next;chase!=NULL;){
		struct good* temp=chase;
		chase=chase->next;
		free(temp);
	}
	list->next=NULL;
	list->total_number=0;
	return;
}
void updateWare(FILE** nowware,struct good* list){
	rewind(*nowware);
	fprintf(*nowware,"%s %d\n",list->warename,list->total_number);
	struct good* p[list->total_number];
	int cnt=0;
	for(struct good* chase=list->next->next;chase!=NULL;chase=chase->next){
		p[cnt]=chase;
		cnt++;
	}
	cnt--;
	for(int i=cnt;i>=0;i--){
		fprintf(*nowware,"%s %d\n",p[i]->form,p[i]->number);
	}
	return;
}
void closeWare(FILE** nowware,struct good* list){
	updateWare(nowware,list);
	if(	fclose(*nowware)){
		printf("关闭文件错误\n");
	}else{
		*nowware=NULL;
		deleteList(list);
		printf("关闭文件成功\n\n");
		printf("选择功能（请输入对应编号）：\n");
		printf("1:新建仓库\n");
		printf("2:打开仓库\n");
		printf("0:结束程序\n");
	}
	return;
}
void printWare(struct good* list){
	printf("货物总数：%d\n\n",list->total_number);
	for(struct good* chase=list->next->next;chase!=NULL;chase=chase->next){
		printf("%s\t\t%d\n",chase->form,chase->number);
	}
	return;
}
struct good* findgoodfa(struct good* list,char* aim){
	struct good* chase=list->next;
	for(;chase->next!=NULL&&memcmp(chase->next->form,aim,strlen(aim));){
		chase=chase->next;
	}
	return chase;
}
void inPut(struct good* list){
	char newform[128];
	int cnt=0;
	printf("待入库货物型号：");
	scanf("%s",newform);
	printf("待入库货物数量：");
	scanf("%d",&cnt);
	struct good* aim=findgoodfa(list,newform);
	if(aim->next==NULL){
		strcpy(list->next->form,newform);
		list->next->number=cnt;
		addnode(list);
		list->total_number++;
	}else{
		aim->next->number+=cnt;
	}
	printf("入库成功。\n\n");
	printf("选择功能（请输入对应编号）：\n");
	printf("3:关闭当前仓库\n");
	printf("4:从当前仓库入库\n");
	printf("5:从当前仓库出库\n");
	printf("6:显示当前仓库列表\n");
	printf("0:结束程序\n");
	return;
}
void outPut(struct good* list){
	char outform[128];
	int cnt=0;
	printf("待出库货物型号：");
	scanf("%s",outform);
	printf("待出库货物数量：");
	scanf("%d",&cnt);
	struct good* aimfa=findgoodfa(list,outform);
	if(aimfa->next==NULL){
		printf("仓库中无该货物记录。\n");
	}else{
		struct good* temp=aimfa->next;
		temp->number-=cnt;
		if(temp->number<=0){
			aimfa->next=temp->next;
			free(temp);
		}
		printf("出库完成。\n");
	}
	printf("选择功能（请输入对应编号）：\n");
	printf("3:关闭当前仓库\n");
	printf("4:从当前仓库入库\n");
	printf("5:从当前仓库出库\n");
	printf("6:显示当前仓库列表\n");
	printf("0:结束程序\n");
	return;
}
int main(){
	int option;
	struct good* list=(struct good*)malloc((sizeof(struct good)));
	list->next=NULL;
	FILE* filestream=NULL;
	char* name=(char*)malloc(sizeof(char)*128);
	printf("欢迎使用仓库管理系统！\n");
	printf("选择功能（请输入对应编号）：\n");
	printf("1:新建仓库\n");
	printf("2:打开仓库\n");
	printf("3:关闭当前仓库\n");
	printf("4:从当前仓库入库\n");
	printf("5:从当前仓库出库\n");
	printf("6:显示当前仓库列表\n");
	printf("0:结束程序\n");
	scanf("%d",&option);
	fflush(stdin);
	while(1){
	switch (option) {
		case 0:
			if(filestream){
				printf("尚有仓库未被关闭，请在关闭仓库后退出。\n");
				scanf("%d",&option);
				fflush(stdin);
			}else{
				return 0;	
			}
			break;
		case 1:
			if(filestream){
				printf("尚有仓库未被关闭，请在关闭仓库后操作。\n");
			}else{
			printf("请输入新仓库的名字：");
			gets(name);
			newWare(&filestream,name);
			}
			scanf("%d",&option);
			fflush(stdin);
			break;
		case 2:
			if(filestream){
				printf("尚有仓库未被关闭，请在关闭仓库后操作。\n");
			}else{	
				printf("请输入仓库的名字：");
				gets(name);
				openWare(&filestream,list,name);
			}
			scanf("%d",&option);
			fflush(stdin);
			break;
		case 3:
			if(!filestream){
				printf("当前没有打开的仓库。\n");
			}else{	
			closeWare(&filestream,list);
			scanf("%d",&option);
			}
			fflush(stdin);
			break;
		case 4:
			if(!filestream){
				printf("当前没有打开的仓库。\n");
			}else{
			inPut(list);
			}
			scanf("%d",&option);
			fflush(stdin);
			break;
		case 5:
			if(!filestream){
				printf("当前没有打开的仓库。\n");
			}else{
			outPut(list);
			}
			scanf("%d",&option);
			fflush(stdin);
			break;
		case 6:
			if(!filestream){
				printf("当前没有打开的仓库。\n");
			}else{
			printWare(list);
			}
			scanf("%d",&option);
			fflush(stdin);
			break;
		default:
			printf("错误操作。\n");
			printf("选择功能（请输入对应编号）：\n");
			printf("1:新建仓库\n");
			printf("2:打开仓库\n");
			printf("3:关闭当前仓库\n");
			printf("4:从当前仓库入库\n");
			printf("5:从当前仓库出库\n");
			printf("6:显示当前仓库列表\n");
			printf("0:结束程序\n");
			scanf("%d",&option);
			fflush(stdin);
			break;
	}
	}
	return 0;
}
