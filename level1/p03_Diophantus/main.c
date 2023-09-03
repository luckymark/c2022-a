#include <stdio.h>

int main() {
    float age;
    for(age= 20.0;age <= 100.0;age++)
    {
        if (age/6.0+age/12.0+age/7.0+5.0+age/2+4.0 == age)
            printf_s("¶ù×ÓËÀÊ±¶ª·¬Í¼%dËê\n",(int)age-4);
    };

    return 0;
}

