CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lX11

SRC = main.c $(wildcard src/*c)
OBJ = $(SRC:.c=.o)
BIN = startony

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean