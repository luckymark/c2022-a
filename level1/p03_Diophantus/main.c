#include <stdio.h>

int main() {
    int age,n;
    for(age=1;age!=n;age++) {
        if (age % 12 == 0 && age % 7 == 0 && (age / 6 + age / 12 + age / 7 + 5 + 4) == age / 2)
            n=age;
    }
    printf("�ʶ�����ʱ����ͼΪ%d��",age -4 );
    return 0;
}
