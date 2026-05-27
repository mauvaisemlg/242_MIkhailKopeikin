#include <stdio.h>

void __wrap_fred()
{
    puts("fred is called");
}

void __wrap_john()
{
    puts("john is called");
}