cargo build
mkdir build 2> /dev/null
cd build
gcc -c ../src/wrapper.c -o wrapper.o
ar crsT wrapper.a wrapper.o ../target/debug/liblibrary.a
gcc -c ../src/test.c -o test.o
gcc test.o wrapper.a -o exec