#include <iostream>
 
int main()
{
    float i;
    for(i = 20.0;i<100.0;i++)
    {
        if(i/6.0+i/12.0+i/7.0+5.0+i/2.0+4.0 == i)
        {
            std::cout<<"Diophantus lived "<<(int)i<<" years\n";
        }
    }
    return 0;
}
