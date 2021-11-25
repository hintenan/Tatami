#include <stdio.h>
#include <stdlib.h>
//#include <dlfcn.h>
#include "header.h"




int arithmetic(char op, int num1, int num2)
{
    if (op == '+')
        return (num1 + num2);
    if (op == '-')
        return (num1 - num2);
    if (op == '*')
        return (num1 * num2);
    if (op == '/')
        return (num1 /num2);
    return (0);
}
