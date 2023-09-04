#include <stdio.h>
#include <stdlib.h>

int main(){
    char *c;
    int val = 524;
    itoa(val, c, 10);
    printf("%s\n", c);
    return 0;
}
