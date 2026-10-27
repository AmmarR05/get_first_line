#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
void testfun()
{
    static int a = 0;
    int b = 0;
    a++;
    b++;
    printf("%d  %d \n" , a , b);
}
int main()
{
    testfun();
    testfun();
    testfun();
    testfun();

}
