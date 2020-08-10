#include <stdio.h>
#include "bigint.h"

int main()
{
    bigint a, b, c;
    char sa[256], sb[256];
    
    scanf("%s", sa);
    scanf("%s", sb);
    
    bigint_from_str(sa, &a);
    bigint_from_str(sb, &b);
    
    printf("a = ");
    bigint_print(&a);
    printf("b = ");
    bigint_print(&b);
    
    int cmp = bigint_less(&a, &b);
    printf("a %c b\n", cmp == 1 ? '<' : cmp == -1 ? '>' : '=');
    
    bigint_add(&a, &b, &c);
    printf("a + b = ");
    bigint_print(&c);
    
    bigint_subtract(&a, &b, &c);
    printf("a - b = ");
    bigint_print(&c);
    
    bigint_multiply(&a, &b, &c);
    printf("a * b = ");
    bigint_print(&c);
    
    bigint_divide(&a, &b, &c);
    printf("a div b = ");
    bigint_print(&c);
    
    bigint_power(&a, 5, &c);
    printf("a^5 = ");
    bigint_print(&c);
    
    bigint_power(&b, 8, &c);
    printf("b^8 = ");
    bigint_print(&c);
    
    return 0;
}