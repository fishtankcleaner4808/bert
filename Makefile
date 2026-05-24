TARGET=bert
CC=gcc
CFLAGS=`sdl2-config --cflags` -c -Wall -Wextra -std=c99 -Iinclude
LIBS=-lSDL2 -lSDL2_ttf -lm

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
