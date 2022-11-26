int main()
{
    int i, x, y, z;//i为测试数，x为个位，y为十位，z为百位
    for (i = 100; i < 1000; i++)
    {
        x = i % 10;
        y = i / 10 % 10;
        z = i / 100 % 10;

        if (i == (x ^3 + y ^ 3 + z ^ 3))
            printf("%d\n", i);

    }
    return 0;
}
