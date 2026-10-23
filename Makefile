CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -fstack-protector
TARGET = main
SRC = main.c Modification.c svg.c the_almighty.c

.PHONY: all build run clean

all: $(TARGET)

$(TARGET): $(SRC) shapes.h
	$(CC) $(CFLAGS) $(SRC) -o $@

build: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)