#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<w32api.h>
#include<stdbool.h>
//#include<graphics.h>
#define N 16
bool isWin=false;//游戏结束判断
struct location{//坐标对
	int x;
	int y;
};
char** right(char** map,struct location* player){
	if(player->x==N||map[player->y-1][player->x]=='X'){//靠短路避免溢出
		return map;
	}
	if(map[player->y-1][player->x]=='!'){
		isWin=true;
		map[player->y-1][player->x]=map[player->y-1][player->x-1];
		map[player->y-1][player->x-1]=' ';
		player->x+=1;
		return map;
	}
	char temp=map[player->y-1][player->x-1];
	map[player->y-1][player->x-1]=map[player->y-1][player->x];
	map[player->y-1][player->x]=temp;
	player->x+=1;
	return map;
}
char** left(char** map,struct location* player){
	if(player->x==1||map[player->y-1][player->x-2]=='X'){
		return map;
	}
	if(map[player->y-1][player->x-2]=='!'){
		isWin=true;
		map[player->y-1][player->x-2]=map[player->y-1][player->x-1];
		map[player->y-1][player->x-1]=' ';
		player->x-=1;
		return map;
	}
	char temp=map[player->y-1][player->x-1];
	map[player->y-1][player->x-1]=map[player->y-1][player->x-2];
	map[player->y-1][player->x-2]=temp;
	player->x-=1;
	return map;
}
char** down(char** map,struct location* player){
	if(player->y==N||map[player->y][player->x-1]=='X'){
		return map;
	}
	if(map[player->y][player->x-1]=='!'){
		isWin=true;
		map[player->y][player->x-1]=map[player->y-1][player->x-1];
		map[player->y-1][player->x-1]=' ';
		player->y+=1;
		return map;
	}
	char temp=map[player->y-1][player->x-1];
	map[player->y-1][player->x-1]=map[player->y][player->x-1];
	map[player->y][player->x-1]=temp;
	player->y+=1;
	return map;
}
char** up(char** map,struct location* player){
	if(player->y==1||map[player->y-2][player->x-1]=='X'){
		return map;
	}
	if(map[player->y-2][player->x-1]=='!'){
		isWin=true;
		map[player->y-2][player->x-1]=map[player->y-1][player->x-1];
		map[player->y-1][player->x-1]=' ';
		player->y-=1;
		return map;
	}
	char temp=map[player->y-1][player->x-1];
	map[player->y-1][player->x-1]=map[player->y-2][player->x-1];
	map[player->y-2][player->x-1]=temp;
	player->y-=1;
	return map;
}
//移动方法，这里是靠高频率刷新实现移动操作，所以当刷新率不高的时候就会出现触发不了的情况（大概？）
//win32api的GetAsyncKeyState函数，识别调用时键盘的触发情况
void move(char** map,struct location* player){
	int direction;
		direction=GetAsyncKeyState(VK_UP);
		if(direction==-32768){//返回INT16_MIN表明该按键处于按下状态
			up(map,player);
		}
		direction=GetAsyncKeyState(VK_DOWN);
		if(direction==-32768){
			down(map,player);
		}
		direction=GetAsyncKeyState(VK_LEFT);
		if(direction==-32768){
			left(map,player);
		}
		direction=GetAsyncKeyState(VK_RIGHT);
		if(direction==-32768){
			right(map,player);
		}
}
void printMap(char** map){
	for(int j=0;j<N;j++){
		for(int i=0;i<N;i++){
			printf("%c",map[j][i]);
		}
		printf("\n");
	}
}
int main(){
	char** map;
	map=(char**)malloc(N*sizeof(char*));
	for(int i=0;i<N;i++){
		map[i]=(char*)malloc(N*sizeof(char));
	}
	struct location player;
	player.x=2;
	player.y=2;
	FILE* fmap;
	fmap=fopen("test.txt","r");//只读模式
	if(fmap){//判断是否正常打开文件
		for(int j=0;j<N;j++){
			for(int i=0;i<N;i++){
				map[j][i]=getc(fmap);
			}
			getc(fmap);
		}
	}else{
		printf("fail");
		return -1;
	}
	while(1){//类似unity的update()的处理
		Sleep(10);
		move(map,&player);
		printMap(map);
		if(isWin){
			printf("\nyou win!\n");
			break;
		}
		system("cls");
	}
	for(int i=0;i<N;i++){//释放内存
		free(map[i]);
	}
	free(map);
	return 0;
}
