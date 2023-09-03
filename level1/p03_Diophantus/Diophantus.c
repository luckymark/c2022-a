#include <stdio.h>
#include <stdlib.h>
int main()
{
    int age=0;
    int agemax=200;
    for(age=0;age<agemax;age++){
        if(age%6==0&&age%12==0&&age%7==0&&age/6+age/12+age/7+5+age/2+4==age){
            printf("年龄为%d\n",age);
            break;
        }
    }
    
    system("pause");
    return 0;
}