OUTPUT_FILE_NAME=myhello

CC=g++

DEPS=-pthread

build: main.o
	$(CC) $(DEPS)  main.o -lm -o $(OUTPUT_FILE_NAME)

main.o: main.cpp
	@$(CC) $(DEPS) -c main.cpp

run:
	./$(OUTPUT_FILE_NAME)
