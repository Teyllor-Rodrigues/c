#include <stdio.h>

int main()
{

    int x1 = 100, x2 = 20;
    int *p;
    p = &x2 + x1;
    printf("%d\n",p);
    x2 = 2 * *p;
    x1 = *p * x2;
    printf("what : %d %d %d\n\n", x1, x2, *p);
    return 0;
}