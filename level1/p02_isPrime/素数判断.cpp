int isPrime(int N)
{
    int j;
    for (j = 2; j<N;j++)
    {
        if (N % j == 0)   
        {
            return 1;
        }
    }
    return 0;    
}