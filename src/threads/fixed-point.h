#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

// fixed point of 17.14

int32_t add(int32_t x , int32_t y);
int32_t add_int(int32_t x , int32_t n);
int32_t subtract(int32_t x , int32_t y);
int32_t subtract_int(int32_t x , int32_t n);
int32_t multiply(int32_t x , int32_t y);
int32_t multiply_int(int32_t x , int32_t n);
int32_t divide(int32_t x , int32_t y);
int32_t divide_int(int32_t x , int32_t n);
int32_t convert_to_fixed(int32_t n);
int32_t convert_frac_to_fixed(int32_t num, int32_t den);
int convert_to_int_round (int32_t x);
int convert_to_int_truncate (int32_t x);

#endif