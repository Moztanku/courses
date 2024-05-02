all: main
main: main.o rozwiazanie.o f.o
	clang -Wextra -o main main.o rozwiazanie.o f.o -lm
main.o: main.c
	clang -c main.c
rozwiazanie.o: rozwiazanie.c
	clang -c rozwiazanie.c
f.o: f.c
	clang -c f.c
clean:
	rm -f main *.o *~
