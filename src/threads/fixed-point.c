#include "threads/fixed-point.h"

// 2^14
int32_t f = 16384;

int32_t 
add (int32_t x , int32_t y)
{
	return x + y;
}

int32_t 
add_int (int32_t x , int32_t n)
{
	return x + n*f;
}

int32_t 
subtract (int32_t x , int32_t y)
{
	return x - y;
}

int32_t
subtract_int (int32_t x , int32_t n)
{
	return x - n*f;
}

int32_t 
multiply (int32_t x , int32_t y)
{
	return ((int64_t) x) * y / f;
}

int32_t 
multiply_int (int32_t x , int32_t n)
{
	return x * n;
}

int32_t 
divide (int32_t x , int32_t y)
{
	return ((int64_t) x) * f / y;
}

int32_t 
divide_int (int32_t x , int32_t n)
{
	return x / n;
}

int32_t 
convert_to_fixed (int32_t n)
{
	return n * f;
}

int32_t 
convert_frac_to_fixed (int32_t num, int32_t den)
{
	return num * f / den;
}

int 
convert_to_int_round (int32_t x)
{
	return x >= 0 ? (x + f / 2) / f : (x - f / 2) / f;

}

int 
convert_to_int_truncate (int32_t x)
{
	return x / f;

}