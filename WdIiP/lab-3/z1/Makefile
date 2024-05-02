# Makefile
all: main
main: main.o isPalindrome.o
	clang -o main main.o isPalindrome.o
main.o: main.c
	clang -c main.c
isPalindrome.o: isPalindrome.c
	clang -c isPalindrome.c
clean:
	rm -f main *.o *~
