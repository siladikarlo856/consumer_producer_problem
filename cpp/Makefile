OUTPUT_FILE_NAME=consumer_producer_cpp.out

CC=g++

DEPS=-pthread

buildrun:
	make build
	./$(OUTPUT_FILE_NAME)

build: main.o
	$(CC) $(DEPS)  main.o -lm -o $(OUTPUT_FILE_NAME)

main.o: main.cpp
	@$(CC) $(DEPS) -c main.cpp

run:
	./$(OUTPUT_FILE_NAME)
