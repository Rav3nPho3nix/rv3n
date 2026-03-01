main: main.c unit-test.h
	gcc main.c -o main.out -g -pg

clean:
	rm *.out