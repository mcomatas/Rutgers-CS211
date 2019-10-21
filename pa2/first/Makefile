all: first
first: first.c
	gcc -Wall -Werror -fsanitize=address first.c -o first
clean:
	rm -rf first

LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm
