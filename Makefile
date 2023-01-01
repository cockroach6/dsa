SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, obj/%.o, $(SRCS))
CFLAGS=-I inc
CC=gcc

all: dsa

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

dsa: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	@rm -rf obj/*

re: clean all
