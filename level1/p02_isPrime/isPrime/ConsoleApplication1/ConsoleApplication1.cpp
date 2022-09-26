#include <stdio.h>
#include <math.h>
void main()
{
    int m;  // 输入的整数 
    int i;  // 循环次数
    int k;  // m 的平方根 

    printf("输入一个整数：");
    scanf_s("%d", &m);

    // sqrt()的参数为 double 类型，强制转换m的类型 
    k = (int)sqrt((double)m);
    for (i = 2; i <= k; i++)
        if (m % i == 0)
            break;

    // 如果完成所有循环，那么m为素数
    if (i > k)
        printf("%d是素数。\n", m);
    else
        printf("%d不是素数。\n", m);
}
