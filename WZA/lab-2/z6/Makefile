# My makefile for compiling single source C, C++, C++2, Go and Haskell programs

C = clang
CFLAGS = -std=c17 -O3

CC = clang++
CXXFLAGS = -std=c++20 -O3 -I inc

CC2 = cppfront
CXX2FLAGS = -pure-cpp2 -output stdout

RS = rustc
RSFLAGS = -O

GO = go
GOFLAGS = build

HS = ghc
HSFLAGS = -O3

SRC_DIR = src
BIN_DIR = bin

SOURCES := \
	$(wildcard $(SRC_DIR)/*.c)\
	$(wildcard $(SRC_DIR)/*.cpp)\
	$(wildcard $(SRC_DIR)/*.cpp2)\
	$(wildcard $(SRC_DIR)/*.rs)\
	$(wildcard $(SRC_DIR)/*.go)

BINARIES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))
BINARIES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(BINARIES))
BINARIES := $(patsubst $(SRC_DIR)/%.cpp2, $(BIN_DIR)/%, $(BINARIES))
BINARIES := $(patsubst $(SRC_DIR)/%.rs, $(BIN_DIR)/%, $(BINARIES))
BINARIES := $(patsubst $(SRC_DIR)/%.go, $(BIN_DIR)/%, $(BINARIES))

all: $(BIN_DIR) $(BINARIES)

$(BIN_DIR):
	$(info Creating directory: $@)
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(info Compiling C: $< -> $@)
	@$(C) $(CFLAGS) $< -o $@

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(info Compiling C++: $< -> $@)
	@$(CC) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp2
	$(info Compiling C++2: $< -> $@)
	@$(CC2) $(CXX2FLAGS) $< 2> /dev/null 1| $(CC) $(CXXFLAGS) -o $@ -x c++ -

$(BIN_DIR)/%: $(SRC_DIR)/%.rs
	$(info Compiling Rust: $< -> $@)
	@$(RS) $(RSFLAGS) $< -o $@

$(BIN_DIR)/%: $(SRC_DIR)/%.go
	$(info Compiling Go: $< -> $@)
	@$(GO) $(GOFLAGS) -o $@ $<

clean:
	$(info Removing directory: $(BIN_DIR))
	@rm -r $(BIN_DIR)

.PHONY: all clean