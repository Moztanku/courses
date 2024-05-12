mkdir build 2> /dev/null
find src -name "*.java" > build/sources.txt
javac @build/sources.txt  -d build
java -cp build Main