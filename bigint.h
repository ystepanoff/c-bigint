#pragma once

#include <stdio.h>
#include <memory.h>
#include <string.h>

#define MAX_DIGITS 1000000

typedef struct 
{
    int sign, n;
    char d[MAX_DIGITS];
} bigint;


void bigint_init(bigint *a);
void bigint_print(bigint *a);

void bigint_add(bigint *a, bigint *b, bigint *result);
void bigint_subtract(bigint *a, bigint *b, bigint *result);
void bigint_multiply(bigint *a, bigint *b, bigint *result);
void bigint_divide(bigint *a, bigint *b, bigint *result);

void bigint_power(bigint *a, int n, bigint *result);

int bigint_less(bigint *a, bigint *b);

void bigint_justify(bigint *a);
void bigint_shift(bigint *a, int n);

void bigint_from_int(int n, bigint *result);
void bigint_from_str(char n[], bigint *result);