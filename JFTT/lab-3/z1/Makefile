SRC_DIR = src
BIN_DIR = build

CC = gcc
CFLAGS = -Wall -Wno-unused -I$(SRC_DIR) -I$(BIN_DIR) -DGF_P=1234577

# List of sources and generated files
SRCS = galois.c print.c
OBJS = $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o)) $(BIN_DIR)/parser.tab.o $(BIN_DIR)/lexer.o

# Targets
all: $(BIN_DIR) $(BIN_DIR)/main

clean:
	rm -rf $(BIN_DIR)

just-main: $(BIN_DIR)/main
	rm -f $(OBJS) $(BIN_DIR)/*.c $(BIN_DIR)/*.h

$(BIN_DIR):
	mkdir -p $@

# Pattern rules
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Lexer and parser rules
$(BIN_DIR)/lexer.o: $(SRC_DIR)/lexer.l $(BIN_DIR)/parser.tab.h
	flex -o $(BIN_DIR)/lexer.c $<
	$(CC) $(CFLAGS) -c $(BIN_DIR)/lexer.c -o $@

$(BIN_DIR)/parser.tab.c $(BIN_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	bison -d $< -o $(BIN_DIR)/parser.tab.c

$(BIN_DIR)/parser.tab.o: $(BIN_DIR)/parser.tab.c $(BIN_DIR)/parser.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

# Link main executable
$(BIN_DIR)/main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Phony targets
.PHONY: all clean just-main
