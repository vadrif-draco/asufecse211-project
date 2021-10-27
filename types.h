// Include Guard
#ifndef TYPES_H
#define TYPES_H

// Datatypes fetched from https://www.keil.com/support/man/docs/armcc/armcc_chr1359125009502.htm

typedef signed char int8;
typedef signed char* int8_ptr;

typedef unsigned char uint8;
typedef unsigned char* uint8_ptr;

typedef signed short int16;
typedef signed short* int16_ptr;

typedef unsigned short uint16;
typedef unsigned short* uint16_ptr;

typedef signed int int32;
typedef signed int* int32_ptr;

typedef unsigned int uint32;
typedef unsigned int* uint32_ptr;

// No need to typedef long; int covers it.

typedef signed long long int64;
typedef signed long long* int64_ptr;

typedef unsigned long long uint64;
typedef unsigned long long* uint64_ptr;

typedef float float32;
typedef float* float32_ptr;

typedef double float64;
typedef double* float64_ptr;

// No need to typedef long double; it is the same as double

#endif /* TYPES_H */
