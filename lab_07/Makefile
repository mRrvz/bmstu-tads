CFILES := $(wildcard src/*.c)
FLAGS := -Wall -std=c99 -lm
DEBUG_FLAGS := -DDEBUG -g

ifeq (debug,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

app.exe: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) $^ -o $@ 

debug: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe 

run: app.exe
	./app.exe

clean:
	rm *.o *.exe *.d *.out *.dot *.png

%.o: src/%.c
	gcc $(FLAGS) -c -MD $< 

include $(wildcard *.d)
