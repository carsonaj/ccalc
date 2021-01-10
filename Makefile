all: tests objects

matrix_tests: matrix_tests.c matrix.c array.c
	gcc matrix_tests.c matrix.c array.c -o matrix_tests

array_tests: array_tests.c array.c
	gcc array_tests.c array.c -o array_tests

matrix.o: matrix.c 
	gcc -c matrix.c -o matrix.o

array.o: array.c 
	gcc -c array.c -o array.o

objects: array.o matrix.o

tests: array_tests matrix_tests
	./array_tests ./matrix_tests

clean: 
	rm array_tests matrix_tests array.o matrix.o