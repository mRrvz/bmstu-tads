CFILES := $(wildcard src/*.c)
FLAGS := -Wall -std=c99 
DEBUG_FLAGS := -DDEBUG -g

ifeq (debug,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

app.exe: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) -O2 $^ -o $@

DEBUG: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) -g $^ -o app.exe

run: app.exe
	./app.exe

clean: 
	rm *.o *.exe *.d *.out

%.o: src/%.c 
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
