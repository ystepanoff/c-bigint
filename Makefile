test:bigint.o
	cc -o test test.c bigint.c

bigint.o:
	cc -c bigint.c