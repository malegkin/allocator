#pragma once

//#include "stdafx.h"

constexpr uint64_t factorial(const uint64_t n) { 
    //factorial of number greater than 22 exceeds the maximum allowable value for uint_64_t 
    if (n > 22)
        return 0;

    return n ? n * factorial(n - 1) : 1;
} 


static_assert(factorial(0) == 1);
static_assert(factorial(1) == 1);
static_assert(factorial(2) == 2);
static_assert(factorial(3) == 2*3);
static_assert(factorial(4) == 2*3*4);
static_assert(factorial(5) == 2*3*4*5);
static_assert(factorial(6) == 2*3*4*5*6);
static_assert(factorial(7) == 2*3*4*5*6*7);
static_assert(factorial(8) == 2*3*4*5*6*7*8);
static_assert(factorial(9) == 2*3*4*5*6*7*8*9);
static_assert(factorial(10) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10);
static_assert(factorial(11) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11);
static_assert(factorial(12) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12);
static_assert(factorial(13) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13);
static_assert(factorial(14) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14);
static_assert(factorial(15) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15);
static_assert(factorial(16) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16);
static_assert(factorial(17) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17);
static_assert(factorial(18) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18);
static_assert(factorial(19) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19);
static_assert(factorial(20) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20);
static_assert(factorial(21) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20*21);
static_assert(factorial(22) == static_cast<uint64_t>(2)*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20*21*22);
static_assert(factorial(23) == 0);








