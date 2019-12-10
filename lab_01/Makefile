CFILES := $(wildcard *.c)
OBJECTS := $(CFILES:%.c=%.o)
FLAGS := -Wall -pedantic -std=c99
app.exe: $(OBJECTS) *.h
	gcc $(FLAGS) $(OBJECTS) -o app.exe
%.o: %.c *.h
	gcc $(FLAGS) -c $<
run: app.exe
	./app.exe
clean: 
	rm *.o *.exe
