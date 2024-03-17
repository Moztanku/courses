mkdir build 2> /dev/null
cd build
gcc -std=c99 -Wall -c ../iter.c -o iter.o
gnatmake -gnatX0 -c ../main.adb -o main.ali
gnatmake -gnatX0 -c ../wrapper.ads -o wrapper.ali
gnatbind main.ali wrapper.ali
gnatlink -o exec main.ali iter.o