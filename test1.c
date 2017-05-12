#include <stdio.h>
#include <stdlib.h>

int* fun(){
    int* m = malloc(sizeof(int) * 2);
    return NULL;
}

int main(){
    int* a = fun();
    free(a);
    return 0;
}