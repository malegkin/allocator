#include "../include/stdafx.h"
#include "../include/foo.h"


uint64_t factorial(const size_t n)
{
    return (n < 2) ? 1 : factorial(n - 1) * n ;
}

