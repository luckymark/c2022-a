#include<stdio.h>
const int ages=6*12*7*2;//防止用浮点造成数据丢失，就设了一个所有分数分母的最小公倍数
						//同时注意到这个ages依照常理应该比正常人类寿命大，所以必然是
						//正常年龄的放大
int main(){
	int childage;
	int teenage;
	int bachelor;
	int sondeath;
	int rAge;
	childage=ages/6;
	teenage=ages/12;
	bachelor=ages/7;
	sondeath=ages/2;
	int nineyears=ages-childage-teenage-bachelor-sondeath;
	//排除掉ages中所有分数表示的年数
	//最后得到的年数9年（nineyears是被放大的9年）
	rAge=ages/(nineyears/9);//算出放大倍数，然后拿去除ages，得到真实寿命;
	printf("当丢番图死时，他的年龄为：%d",rAge-4);
	return 0;
}
