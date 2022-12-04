CC ?= gcc

SRC := $(wildcard src/*.c)
BIN := graser

all: build

build:
	$(CC) $(SRC) -lSDL2 -lreadline -o $(BIN)

run: build
	./$(BIN)
