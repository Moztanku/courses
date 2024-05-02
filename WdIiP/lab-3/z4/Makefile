all: main
main: main.o north.o south.o east.o west.o distance.o newagent.o
	clang -Wextra -o main main.o north.o south.o east.o west.o distance.o newagent.o -lm
main.o: main.c
	clang -c main.c
north.o: north.c
	clang -c north.c
south.o: south.c
	clang -c south.c
west.o: west.c
	clang -c west.c
east.o: east.c
	clang -c east.c
distance.o: distance.c
	clang -c distance.c
newagent.o: newagent.c
	clang -c newagent.c
clean:
	rm -f main *.o *~
