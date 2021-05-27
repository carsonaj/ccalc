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

tests: type_tests array_tests integer_tests matrix_tests polynomial_tests
	test/type_tests
	valgrind test/type_tests
	echo
	test/array_tests 
	valgrind test/array_tests
	echo 
	test/integer_tests
	valgrind test/integer_tests
	echo
	test/matrix_tests
	valgrind test/matrix_tests
	echo
	test/polynomial_tests
	valgrind test/polynomial_tests --track-origins=yes
	echo

SRC_FILES = ./src/type.c ./src/integer.c ./src/array.c ./src/matrix.c ./src/polynomial.c
OBJ_FILES = ./obj/array.o ./obj/matrix.o ./obj/polynomial.o

type_tests: 
	gcc ./test/type_tests.c $(SRC_FILES) -o ./test/type_tests

array_tests: 
	gcc ./test/array_tests.c $(SRC_FILES) -o ./test/array_tests

integer_tests:
	gcc ./test/integer_tests.c $(SRC_FILES) -o ./test/integer_tests

matrix_tests: 
	gcc ./test/matrix_tests.c $(SRC_FILES) -o ./test/matrix_tests

polynomial_tests:
	gcc ./test/polynomial_tests.c $(SRC_FILES) -o ./test/polynomial_tests

lib: array.o matrix.o polynomial.o
	gcc -shared $(OBJ_FILES) -o lib/libccalc.so 

polynomial.o:
	gcc -c ./src/polynomial.c -o ./obj/polynomial.o

matrix.o: 
	gcc -c ./src/matrix.c -o ./obj/matrix.o

array.o: 
	gcc -c ./src/array.c -o ./obj/array.o
