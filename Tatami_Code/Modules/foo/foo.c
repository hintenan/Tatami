#include <stdio.h>
#include <stdlib.h>
#include "foo.h"
 
 
void foo(void) {
    puts("Hello, I am a shared library");
}

int add(int num1, int num2) {
    
    return (num1 + num2);
    
}