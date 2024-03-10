mkdir build
cd build
gcc -std=c99 -Wall -c ../wrapper.c -o wrapper.o
gcc -std=c99 -Wall -c ../test.c -o test.o
gnatmake -gnatX0 -c ../recu.adb
gnatbind -n recu.ali
gnatlink -o exec recu.ali wrapper.o test.o