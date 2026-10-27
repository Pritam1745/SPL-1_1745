CC = gcc
CFLAGS = -Wall -Wextra -g

all: stockmate

stockmate: src/main.c src/utils.c src/auth.c src/product.c
	$(CC) $(CFLAGS) -o stockmate src/main.c src/utils.c src/auth.c src/product.c

clean:
	rm -f stockmate