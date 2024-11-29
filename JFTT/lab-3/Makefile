
SRC_DIR = src
BIN_DIR = build

CC = gcc
CFLAGS = -Wall -Wno-unused -lm -I$(SRC_DIR) -I$(BIN_DIR)

all: $(BIN_DIR) $(BIN_DIR)/main

clean:
	rm -rf $(BIN_DIR)

just-main: $(BIN_DIR)/main
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.c $(BIN_DIR)/*.h

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/galois.o: $(SRC_DIR)/galois.c $(SRC_DIR)/galois.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/galois.c -o $(BIN_DIR)/galois.o

$(BIN_DIR)/print.o: $(SRC_DIR)/print.c $(SRC_DIR)/print.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/print.c -o $(BIN_DIR)/print.o

$(BIN_DIR)/parser.tab.c $(BIN_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	bison -d $(SRC_DIR)/parser.y -o $(BIN_DIR)/parser.tab.c

$(BIN_DIR)/parser.tab.o: $(BIN_DIR)/parser.tab.c $(BIN_DIR)/parser.tab.h
	$(CC) $(CFLAGS) -c $(BIN_DIR)/parser.tab.c -o $(BIN_DIR)/parser.tab.o

$(BIN_DIR)/lexer.o: $(SRC_DIR)/lexer.l $(BIN_DIR)/parser.tab.h
	flex -o $(BIN_DIR)/lexer.c $(SRC_DIR)/lexer.l
	$(CC) $(CFLAGS) -c $(BIN_DIR)/lexer.c -o $(BIN_DIR)/lexer.o

$(BIN_DIR)/main: $(BIN_DIR)/galois.o $(BIN_DIR)/print.o $(BIN_DIR)/parser.tab.o $(BIN_DIR)/lexer.o
	$(CC) $(CFLAGS) $(BIN_DIR)/galois.o $(BIN_DIR)/print.o $(BIN_DIR)/parser.tab.o $(BIN_DIR)/lexer.o -o $(BIN_DIR)/main

.PHONY: all clean just-main
