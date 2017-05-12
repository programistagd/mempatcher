#pragma GCC diagnostic ignored "-fpermissive"
#include "patch.hpp"
#include <stdio.h>
#include <stdlib.h>

Ptr<int>  fun(){
    Ptr<int>  m = p_malloc(sizeof(int) * 2);
    return NULL;
}

int main(){
    Ptr<int>  a = fun();
    p_free(a);
    return 0;
}
