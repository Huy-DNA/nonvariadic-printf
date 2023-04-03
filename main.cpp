#include "my_printf.h"

int main() {
    int a = 86;
    const char* b = "Hello World!";
    double f = 86.2003;
    double* p = &f;

    my_printf("%d\n%s\n%f\n%p\n", a, b, f, p);
}