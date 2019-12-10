CFILES := $(wildcard *.c)
FLAGS := -Wall -std=c99

app.exe: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) -O2 $^ -o $@

DEBUG: $(patsubst %.c,%.o,$(CFILES))
	gcc $(FLAGS) -g $^ -o app.exe

run: app.exe
	./app.exe

clean: 
	rm *.o *.exe *.d *.out

%.o: %.c 
	gcc $(FLAGS) -c -MD $<

include $(wildcard *.d)
