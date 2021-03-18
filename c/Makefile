OUTPUT_FILE_NAME=consumer_producer_c.out

CC=gcc

DEPS=-pthread

buildrun:
	make build
	./$(OUTPUT_FILE_NAME)

build: main.o
	$(CC) $(DEPS)  main.o -lm -o $(OUTPUT_FILE_NAME)

main.o: main.c
	@$(CC) $(DEPS) -c main.c

run:
	./$(OUTPUT_FILE_NAME)
