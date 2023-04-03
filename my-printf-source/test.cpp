#include <memory>
#include <cstdio>
#include "my_printf.h"
#include <cstdlib>
#include <climits>
#include <stdexcept>

int main() {
    void* __internal_buffer = malloc(10000);
    void* p_last = __internal_buffer;
   
   *(const char**)p_last= "Hello World!";
    p_last = (char**)p_last + 1;
   
    __realign(p_last, int);
    *(int *)p_last = 86;
    p_last = (int*)p_last + 1;

    __realign(p_last, double);
    *(double*)p_last= (double)86.2003;
    p_last = (double*)p_last + 1;

    __realign(p_last, void*);
    *(const void**)p_last = "Hello World!"; 

    my_printf("%s\n%d\n%f\n%p\n", __internal_buffer);

    free(__internal_buffer); 
}
