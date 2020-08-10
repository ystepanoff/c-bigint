# Yet Another C bigint library

## Description

Providing all the standard arithmetic operations, such as addition, subtraction,
multiplication, integer division, and <img src="https://render.githubusercontent.com/render/math?math=O(\log n)"> time exponentiation.
Fancy things like the Karatsuba algorithm and potentially multiplication based on a fast Fourier transform is yet to come.

## Running the example

The follwing is self-explanatory. Two integers are expected as user input.

```
$ make test
cc -c bigint.c
cc -o test test.c bigint.c
$ ./test
239
100500
a = 239
b = 100500
a < b
a + b = 100739
a - b = -100261
a * b = 24019500
a div b = 0
a^5 = 779811265199
b^8 = 10407070439254381253906250000000000000000
$ ./test
100500
239
a = 100500
b = 239
a > b
a + b = 100739
a - b = 100261
a * b = 24019500
a div b = 420
a^5 = 10252512531281250000000000
b^8 = 10645920227784266881
```
