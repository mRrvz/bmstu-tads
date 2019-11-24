CFILES := $(wildcard src/*.c)
FLAGS := -Wall -std=c99 -lm
DEBUG_FLAGS := -DDEBUG -g

ifeq (debug,$(firstword $(MAKECMDGOALS)))
	FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

app.exe: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) $^ -o $@ -lm

debug: $(patsubst src/%.c,./%.o,$(CFILES))
	gcc $(FLAGS) $^ -o app.exe -lm

run: app.exe
	./app.exe

clean:
	rm *.o *.exe *.d *.out

%.o: src/%.c
	gcc $(FLAGS) -c -MD $< 

include $(wildcard *.d)
