install: build
	sudo mkdir /usr/local/lib/ccalc
	sudo cp -i ./lib/libccalc.so /usr/local/lib/ccalc
	sudo mkdir /usr/local/include/ccalc
	sudo cp -i ./include/*.h /usr/local/include/ccalc
	sudo ldconfig /usr/local/lib/ccalc

uninstall: 
	sudo rm -r /usr/local/lib/ccalc
	sudo rm -r /usr/local/include/ccalc

build: lib

clean: 
	rm -f ./obj/*.o
	rm -f ./lib/*.so
	rm -f ./test/*_tests

tests: array_tests matrix_tests
	test/array_tests 
	valgrind test/array_tests
	test/matrix_tests
	valgrind test/matrix_tests

array_tests: ./test/array_tests.c ./src/array.c
	gcc ./test/array_tests.c ./src/array.c ./src/type.c -o test/array_tests

matrix_tests: 
	gcc ./test/matrix_tests.c ./src/matrix.c ./src/array.c ./src/type.c -o test/matrix_tests

lib: array.o matrix.o
	gcc -shared ./obj/array.o ./obj/matrix.o -o lib/libccalc.so 

matrix.o: 
	gcc -c ./src/matrix.c -o ./obj/matrix.o

array.o: 
	gcc -c ./src/array.c -o ./obj/array.o
