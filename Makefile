install: build
	sudo cp -i ./lib/libccalc.so /usr/local/lib
	sudo cp -i ./include/*.h /usr/local/include
	sudo ldconfig

uninstall: 
	sudo rm /usr/local/lib/libccalc.so
	sudo rm /usr/local/include/array.h /usr/local/include/matrix.h 
	sudo ldconfig

build: lib

tests: array_tests matrix_tests
	test/array_tests 
	valgrind test/array_tests
	test/matrix_tests
	valgrind test/matrix_tests

array_tests: ./test/array_tests.c ./src/array.c
	gcc ./test/array_tests.c ./src/array.c -o test/array_tests

matrix_tests: 
	gcc ./test/matrix_tests.c ./src/matrix.c ./src/array.c -o test/matrix_tests

lib: array.o matrix.o
	gcc -shared ./obj/array.o ./obj/matrix.o -o lib/libccalc.so 

matrix.o: matrix.c 
	gcc -c ./src/matrix.c -o ./obj/matrix.o

array.o: array.c 
	gcc -c ./src/array.c -o ./obj/array.o

clean: 
	rm -f ./obj/*.o
	rm -f ./lib/*.so
	rm -f ./test/*_tests