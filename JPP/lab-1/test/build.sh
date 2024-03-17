mkdir build 2> /dev/null
cd build

gnatmake -gnatX0 -c ../lib.adb
ar cr lib.a lib.o

gcc -c ../wrapper.c
gcc -c ../main.c

gcc main.o wrapper.o lib.a -o exec