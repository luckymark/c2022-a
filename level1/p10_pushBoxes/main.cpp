#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<windows.h>
#include<w32api.h>
#include<stdbool.h>
#define N 16
//09的基础上加上选关系统和箱子对象,修改胜利系统（选关就画了2关意思一下=。=）
bool isWin=false;//胜利判断
int cnt=0;//计步器
enum objectType{Player,Box};
struct location{//存实际坐标，实质已经用作通用游戏对象，y为行，x为列
	int x;
	int y;
	enum objectType type;
};
struct mapsystem{//统合地图以及地图信息
	char** map;//地图本体
	int boxnumber;//地图箱子数
	struct location* boxs;//箱子对象
	struct location player;//玩家对象
	struct location* winchack;//取胜状态
	struct location player_cp;//更新文件用备份
	struct location* boxs_cp;
};
void initialMap(struct mapsystem* newmap){//初始化地图
	newmap->boxnumber=0;
	newmap->map=(char**)malloc(N*sizeof(char*));
	for(int i=0;i<N;i++){
		newmap->map[i]=(char*)malloc(N*sizeof(char));
	}
	newmap->player.type=Player;
}
void chack(struct mapsystem system){//判断是否游戏结束
	for(int i=0;i<system.boxnumber;i++){
		if(system.map[system.winchack[i].y-1][system.winchack[i].x-1]!='B'){
			return;
		}
	}
	isWin=true;
	return;
}
char** right(struct mapsystem system,struct location* object){
	if(object->x==N||system.map[object->y-1][object->x]=='X'){//通用处理
		return system.map;
	}
	if(system.map[object->y-1][object->x]==' '||system.map[object->y-1][object->x]=='!'){
	system.map[object->y-1][object->x]=system.map[object->y-1][object->x-1];
	system.map[object->y-1][object->x-1]=' ';
	object->x+=1;
	if(object->type==Player){
	cnt++;
	}
	return system.map;
	}else if(system.map[object->y-1][object->x]=='B'){//接触box
		int boxcount;
		for(int i=0;i<system.boxnumber;i++){//遍历获取碰撞box的对象
			if(system.boxs[i].x==object->x+1&&system.boxs[i].y==object->y){
				boxcount=i;
				break;
			}
		}
		if(object->type==Player){
			right(system,&system.boxs[boxcount]);
			if(system.map[object->y-1][object->x]==' '){
				system.map[object->y-1][object->x]=system.map[object->y-1][object->x-1];
				system.map[object->y-1][object->x-1]=' ';
				object->x+=1;
				cnt++;
				chack(system);
				return system.map;
			}
		}else{
			return system.map;//B与B碰撞视作X
		}
	}
	return system.map;
}
char** left(struct mapsystem system,struct location* object){
	if(object->x==1||system.map[object->y-1][object->x-2]=='X'){
		return system.map;
	}
	if(system.map[object->y-1][object->x-2]==' '||system.map[object->y-1][object->x-2]=='!'){
	system.map[object->y-1][object->x-2]=system.map[object->y-1][object->x-1];
	system.map[object->y-1][object->x-1]=' ';
	object->x-=1;
	if(object->type==Player){
	cnt++;
	}
	return system.map;
	}
	if(system.map[object->y-1][object->x-2]=='B'){
		int boxcount;
		for(int i=0;i<system.boxnumber;i++){
			if(system.boxs[i].x==object->x-1&&system.boxs[i].y==object->y){
				boxcount=i;
				break;
			}
		}
		if(object->type==Player){
			left(system,&system.boxs[boxcount]);
			if(system.map[object->y-1][object->x-2]==' '){
				system.map[object->y-1][object->x-2]=system.map[object->y-1][object->x-1];
				system.map[object->y-1][object->x-1]=' ';
				object->x-=1;
				cnt++;
				chack(system);
				return system.map;
			}
		}else{
			return system.map;
		}
	}
	return system.map;
}
char** down(struct mapsystem system,struct location* object){
	if(object->y==N||system.map[object->y][object->x-1]=='X'){
		return system.map;
	}
	if(system.map[object->y][object->x-1]==' '||system.map[object->y][object->x-1]=='!'){
	system.map[object->y][object->x-1]=system.map[object->y-1][object->x-1];
	system.map[object->y-1][object->x-1]=' ';
	object->y+=1;
	if(object->type==Player){
	cnt++;
	}
	return system.map;
	}
	if(system.map[object->y][object->x-1]=='B'){
		int boxcount;
		for(int i=0;i<system.boxnumber;i++){
			if(system.boxs[i].x==object->x&&system.boxs[i].y==object->y+1){
				boxcount=i;
				break;
			}
		}
		if(object->type==Player){
			down(system,&system.boxs[boxcount]);
			if(system.map[object->y][object->x-1]==' '){
				system.map[object->y][object->x-1]=system.map[object->y-1][object->x-1];
				system.map[object->y-1][object->x-1]=' ';
				object->y+=1;
				chack(system);
				return system.map;
			}
		}else{
			return system.map;
		}
	}
	return system.map;
}
char** up(struct mapsystem system,struct location* object){
	if(object->y==1||system.map[object->y-2][object->x-1]=='X'){
		return system.map;
	}
	if(system.map[object->y-2][object->x-1]==' '||system.map[object->y-2][object->x-1]=='!'){
	system.map[object->y-2][object->x-1]=system.map[object->y-1][object->x-1];
	system.map[object->y-1][object->x-1]=' ';
	object->y-=1;
	if(object->type==Player){
	cnt++;
	}
	return system.map;
	}
	if(system.map[object->y-2][object->x-1]=='B'){
		int boxcount;
		for(int i=0;i<system.boxnumber;i++){
			if(system.boxs[i].x==object->x&&system.boxs[i].y==object->y-1){
				boxcount=i;
				break;
			}
		}
		if(object->type==Player){
			up(system,&system.boxs[boxcount]);
			if(system.map[object->y-2][object->x-1]==' '){
				system.map[object->y-2][object->x-1]=system.map[object->y-1][object->x-1];
				system.map[object->y-1][object->x-1]=' ';
				object->y-=1;
				chack(system);
				return system.map;
			}
		}else{
			return system.map;
		}
	}
	return system.map;
}
void move(struct mapsystem system,struct location* object){
		if(GetAsyncKeyState(VK_UP)&0x8000){
			up(system,object);
		}
		if(GetAsyncKeyState(VK_DOWN)&0x8000){
			down(system,object);
		}
		if(GetAsyncKeyState(VK_LEFT)&0x8000){
			left(system,object);
		}
		if(GetAsyncKeyState(VK_RIGHT)&0x8000){
			right(system,object);
		}
}
void printMap(struct mapsystem system){
	for(int i=0;i<system.boxnumber;i++){
		system.map[system.winchack[i].y-1][system.winchack[i].x-1]='!';
	}
	system.map[system.player.y-1][system.player.x-1]='@';
	for(int i=0;i<system.boxnumber;i++){
		system.map[system.boxs[i].y-1][system.boxs[i].x-1]='B';
	}
	for(int j=0;j<N;j++){
		for(int i=0;i<N;i++){
			printf("%c",system.map[j][i]);
		}
		printf("\n");
	}
}
int main(){
	struct mapsystem newmap;
	initialMap(&newmap);
	FILE* fmap;
	char level[7];
	printf("请输入关卡数（1~10，输入0结束游戏）：");
	scanf("%s",level);
	getchar();
	if(level[0]=='0'){
		return 0;
	}
	strcat(level,".txt");
	fmap=fopen(level,"r+");
	if(fmap){//以下为初始加载地图，后续应该整合进intialMAP里
		for(int cur=getc(fmap);cur!='\n';cur=getc(fmap)){//取得地图文件中箱子数量
			newmap.boxnumber*=10;
			newmap.boxnumber=newmap.boxnumber+cur-48;
		}
		newmap.boxs=(struct location*)malloc(newmap.boxnumber*sizeof(struct location));
		newmap.boxs_cp=(struct location*)malloc(newmap.boxnumber*sizeof(struct location));
		newmap.winchack=(struct location*)malloc(newmap.boxnumber*sizeof(struct location));
		for(int i=0;i<newmap.boxnumber;i++){//读入取胜条件
			fscanf(fmap,"%d %d",&newmap.winchack[i].x,&newmap.winchack[i].y);
		}
		getc(fmap);
		for(int j=0,cnt=0;j<N;j++){
			for(int i=0;i<N;i++){
				newmap.map[j][i]=getc(fmap);
				if(newmap.map[j][i]=='B'){
					newmap.boxs[cnt].y=j+1;
					newmap.boxs[cnt].x=i+1;
					newmap.boxs[cnt].type=Box;
					newmap.boxs_cp[cnt].y=j+1;
					newmap.boxs_cp[cnt].x=i+1;
					cnt++;
				}//初始化box位置
				if(newmap.map[j][i]=='@'){
					newmap.player.y=j+1;
					newmap.player.x=i+1;
					newmap.player_cp.y=j+1;
					newmap.player_cp.x=i+1;
				}//初始化player位置
			}
			getc(fmap);
		}
	}else{
		printf("fail");
		return -1;
	}
	while(1){//游戏进程本体，采用实时刷新的显示法
		Sleep(10);
		move(newmap,&newmap.player);
		printMap(newmap);
		if(isWin){
			printf("\nyou win!\n");
			break;
		}
		system("cls");
	}
	fclose(fmap);
	FILE* update=fopen(level,"w");//以下为更新文件，后续应该独立整合成一个函数
	fprintf(update,"%d\n",newmap.boxnumber);
	for(int i=0;i<newmap.boxnumber;i++){
		fprintf(update,"%d %d\n",newmap.winchack[i].x,newmap.winchack[i].y);
	}
	newmap.map[newmap.player.y-1][newmap.player.x-1]=' ';
	newmap.map[newmap.player_cp.y-1][newmap.player_cp.x-1]='@';
	for(int i=0;i<newmap.boxnumber;i++){
			newmap.map[newmap.boxs[i].y-1][newmap.boxs[i].x-1]=' ';
			newmap.map[newmap.boxs_cp[i].y-1][newmap.boxs_cp[i].x-1]='B';
	}
	for(int j=0;j<N;j++){
		for(int i=0;i<N;i++){
			putc(newmap.map[j][i],update);
		}
		putc('\n',update);
	}
	fprintf(update,"你此次的步数是：%d",cnt);
	for(int i=0;i<N;i++){
		free(newmap.map[i]);
	}
	free(newmap.map);
	isWin=false;
	main();//原来c里main函数也可以递归啊
	return 0;
}
