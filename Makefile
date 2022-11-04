SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, obj/%.o, $(SRCS))

CC := g++
CFLAGS := -I inc
PRJ := dsa

all: $(PRJ)

init:
	if [ ! -f obj ];then 	\
		mkdir obj; 			\
	fi
	
$(PRJ): $(OBJS)
	gcc $^ -o $@

obj/%.o: src/%.cpp
	gcc -c $< -o $@ $(CFLAGS)

clean:
ifeq ($(PRJ), $(wildcard $(PRJ)))
	rm $(PRJ) obj/*
endif
	clear

re: clean all