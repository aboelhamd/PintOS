#include "threads/fixed-point.h"

/* 17.14 fixed point system */
fixedpoint_t f = 16384; // 2^14

/* Add an integer to a fixed point.
   Integer must be a fixed point. */
fixedpoint_t 
fixedpoint_add (fixedpoint_t x , int n)
{
	return x + n*f;
}

/* Subtract an integer from a fixed point.
   Integer must be a fixed point. */
fixedpoint_t
fixedpoint_subtract (fixedpoint_t x , int n)
{
	return x - n*f;
}

/* Multiply a fixed point by a fixed point.
   Use 64-bit int to avoide overflow. */
fixedpoint_t 
fixedpoint_multiply (fixedpoint_t x , fixedpoint_t y)
{
	return ((int64_t) x) * y / f;
}

/* Divide a fixed point by a fixed point.
   Use 64-bit int to avoide overflow. */
fixedpoint_t 
fixedpoint_divide (fixedpoint_t x , fixedpoint_t y)
{
	return ((int64_t) x) * f / y;
}

/* Convert an integer into fixed point type. */
fixedpoint_t 
fixedpoint_convert_int (int n)
{
	return n * f;
}

/* Convert a fraction into fixed point type.
   Fraction is sent as numerator and denomenator. */
fixedpoint_t 
fixedpoint_convert_frac (int num, int den)
{
	return num * f / den;
}

/* Convert a fixed point into an integer.
   Rounded towards the nearest integer. */
int 
fixedpoint_convert_to_int_round (fixedpoint_t x)
{
	return x >= 0 ? (x + f / 2) / f : (x - f / 2) / f;
}
