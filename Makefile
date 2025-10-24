CC=gcc
CFLAGS=-pthread -Iinclude -O2 -Wall -Wextra
SRC=src/threadpool.c
BIN=threadpool

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
