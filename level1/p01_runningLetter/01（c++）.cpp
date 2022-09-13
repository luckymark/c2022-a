//本来以为c++会简洁点，结果还多打了几行。。
//这个是用了string和两个栈互倒的方法，在前面准备好够用一行的栈内字符串组之后就来回
//在两个栈里倒腾就行
#include<stdlib.h>
#include<string>
#include<stack>
#include<iostream>
using namespace std;
int main(){
	string TheString;
	stack<string> Strings;
	stack<string> ReStrings;
	cin>>TheString;
	Strings.push(TheString);
	int len=TheString.length();
	for(int i=0;i<118-len;i++){
		TheString=' '+TheString;
		Strings.push(TheString);
		cout<<TheString;
		system("cls");
	}
	while(1){
		while(!Strings.empty()){
			cout<<Strings.top();
			ReStrings.push(Strings.top());
			Strings.pop();
			system("cls");
		}
		while(!ReStrings.empty()){
			cout<<ReStrings.top();
			Strings.push(ReStrings.top());
			ReStrings.pop();
			system("cls");
		}
	}
	return 0;
}
