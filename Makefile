CC = g++
OUTPUT_NAME = change_brightness
LINKER = -lfltk

all: execute

execute:
	$(CC) main.cpp -o $(OUTPUT_NAME) $(LINKER)

run:
	./$(OUTPUT_NAME)

clean:
	rm $(OUTPUT_NAME)
