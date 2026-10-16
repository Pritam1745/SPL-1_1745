CC = gcc
CFLAGS = -Wall -Wextra -g

all: stockmate

stockmate: src/main.c src/utils.c
	$(CC) $(CFLAGS) -o stockmate src/main.c src/utils.c

clean:
	rm -f stockmate