main.out: main.c rv3n.h
	gcc main.c --std=c17 -o main.out

clean:
	rm *.out