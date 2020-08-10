#include "bigint.h"


void bigint_init(bigint *a)
{
    memset(a->d, 0, sizeof(a->d));
    a->sign = 1;
    a->n = 0;
}

void bigint_print(bigint *a)
{
    if (a->sign == -1)
        printf("-");
    for (int i = a->n; i >= 0; i--)
        printf("%d", a->d[i]);
    puts("");
}

void bigint_add(bigint *a, bigint *b, bigint *result)
{
    bigint_init(result);
    
    if (a->sign == b->sign)
    {
        result->sign = a->sign;
    } else
    {
        if (a->sign == -1)
        {
            a->sign = 1;
            bigint_subtract(b, a, result);
            a->sign = -1;
        } else
        {
            b->sign = 1;
            bigint_subtract(a, b, result);
            b->sign = -1;
        }
        return;
    }
    
    result->n = 1 + (a->n > b->n ? a->n : b->n);
    
    int carry = 0;
    for (int i = 0; i <= result->n; i++)
    {
        carry += a->d[i] + b->d[i];
        result->d[i] = (char)(carry % 10);
        carry /= 10;
    }

    bigint_justify(result);
}

void bigint_subtract(bigint *a, bigint *b, bigint *result)
{
    bigint_init(result);

    if (a->sign == -1 || b->sign == -1)
    {
        b->sign = 0 - b->sign;
        bigint_add(a, b, result);
        b->sign = 0 - b->sign;
        
        return;
    }

    if (bigint_less(a, b) == 1)
    {
        bigint_subtract(b, a, result);
        result->sign = -1;
        
        return;
    }
    
    result->n = a->n > b->n ? a->n : b->n;
    
    int take = 0, d;
    for (int i = 0; i <= result->n; i++)
    {
        d = a->d[i] - b->d[i] - take;
        if (a->d[i] > 0)
            take = 0;
        if (d < 0)
        {
            d += 10;
            take = 1;
        }
        result->d[i] = (char)(d % 10);
    }

    bigint_justify(result);
}

void bigint_multiply(bigint *a, bigint *b, bigint *result)
{
    bigint_init(result);
    
    bigint row = *a;
    bigint tmp;
    
    for (int i = 0; i <= b->n; i++)
    {
        for (int j = 1; j <= b->d[i]; j++)
        {
            bigint_add(result, &row, &tmp);
            *result = tmp;
        }
        bigint_shift(&row, 1);
    }

    result->sign = a->sign * b->sign;

    bigint_justify(result);
}

void bigint_divide(bigint *a, bigint *b, bigint *result)
{
    bigint_init(result);
    
    int as = a->sign, bs = b->sign;
    result->sign = as * bs;

    a->sign = 1;
    b->sign = 1;

    bigint row, tmp;
    bigint_init(&row);
    bigint_init(&tmp);

    result->n = a->n;

    for (int i = a->n; i >= 0; i--)
    {
        bigint_shift(&row, 1);
        row.d[0] = a->d[i];
        result->d[i] = 0;
        while (bigint_less(&row, b) != 1)
        {
            result->d[i]++;
            bigint_subtract(&row, b, &tmp);
            row = tmp;
        }
    }

    bigint_justify(result);

    a->sign = as;
    b->sign = bs;
}

void bigint_power(bigint *a, int n, bigint *result)
{
    bigint_from_int(1, result);
    
    bigint tmp;
    while (n > 0)
    {
        if (n & 1)
        {
            bigint_multiply(result, a, &tmp);
            *result = tmp;
            n -= 1;
        }
        bigint_multiply(a, a, &tmp);
        *a = tmp;
        n >>= 1;
    }
}

int bigint_less(bigint *a, bigint *b)
{
    if (a->sign == -1 && b->sign == 1)
        return 1;
    if (a->sign == 1 && b->sign == -1)
        return -1;

    if (b->n > a->n)
        return a->sign;
    if (a->n > b->n)
        return 0 - a->sign;

    for (int i = a->n; i >= 0; i--)
    {
        if (a->d[i] > b->d[i])
            return 0 - a->sign;
        if (b->d[i] > a->d[i]) 
            return a->sign;
    }

    return 0;
}

void bigint_justify(bigint *a)
{
    while (a->n && !(a->d[a->n]))
        a->n--;
    if (!(a->n) && !(a->d[0]))
        a->sign = 1;
}

void bigint_shift(bigint *a, int n)
{
    if (!(a->n) && !(a->d[0]))
        return;

    for (int i = a->n; i >= 0; i--)
        a->d[i+n] = a->d[i];

    for (int i = 0; i < n; i++)
        a->d[i] = 0;

    a->n += n;
}   

void bigint_from_int(int n, bigint *a)
{
    bigint_init(a);
    a->sign = n >= 0 ? 1 : -1;
    
    int m = n >= 0 ? n : -n;
    for (; m > 0; m /= 10)
        a->d[a->n++] = m % 10;
    a->n--;
        
    if (m == 0)
        a->n = 0;
}

void bigint_from_str(char n[], bigint *a)
{
    bigint_init(a);
    
    int m = strlen(n);
    if (!m)
        return;
    
    if (n[0] == '-')
        a->sign = -1;
        
    for (int i = m - 1; i >= (a->sign == 1 ? 0 : 1); i--)
        a->d[a->n++] = n[i] - '0';
    a->n--;
}