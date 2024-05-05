mkdir build 2> /dev/null
javac src/Main.java src/GF1234577.java src/DHSetup.java src/User.java src/UserTest.java -d build
java -cp build Main