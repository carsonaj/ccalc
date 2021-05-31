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

tests: type_tests integer_tests array_tests  modular_int_tests matrix_tests polynomial_tests
	test/type_tests
	valgrind test/type_tests
	echo
	test/array_tests 
	valgrind test/array_tests
	echo 
	test/integer_tests
	valgrind test/integer_tests
	echo
	test/modular_int_tests
	valgrind test/modular_int_tests
	echo 
	test/polynomial_tests
	valgrind test/polynomial_tests --track-origins=yes
	echo
	test/matrix_tests
	valgrind test/matrix_tests
	echo

SRC_FILES = ./src/type.c ./src/array.c ./src/integer.c ./src/modular_int.c ./src/matrix.c ./src/polynomial.c
OBJ_FILES = ./obj/type.o ./obj/array.o ./obj/integer.o ./obj/modular_int.o ./obj/matrix.o ./obj/polynomial.o

type_tests: 
	gcc ./test/type_tests.c $(SRC_FILES) -o ./test/type_tests

array_tests: 
	gcc ./test/array_tests.c $(SRC_FILES) -o ./test/array_tests

integer_tests:
	gcc ./test/integer_tests.c $(SRC_FILES) -o ./test/integer_tests

modular_int_tests: 
	gcc ./test/modular_int_tests.c $(SRC_FILES) -o ./test/modular_int_tests

polynomial_tests:
	gcc ./test/polynomial_tests.c $(SRC_FILES) -o ./test/polynomial_tests

matrix_tests: 
	gcc ./test/matrix_tests.c $(SRC_FILES) -o ./test/matrix_tests

lib: type.o array.o integer.o modular_int.o polynomial.o matrix.o 
	gcc -shared $(OBJ_FILES) -o lib/libccalc.so 

type.o:
	gcc -c ./src/type.c -o ./obj/type.o

array.o: 
	gcc -c ./src/array.c -o ./obj/array.o

integer.o:
	gcc -c ./src/integer.c -o ./obj/integer.o

modular_int.o:
	gcc -c ./src/modular_int.c -o ./obj/modular_int.o

polynomial.o:
	gcc -c ./src/polynomial.c -o ./obj/polynomial.o

matrix.o: 
	gcc -c ./src/matrix.c -o ./obj/matrix.o

