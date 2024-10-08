CC = gcc
CFLAGS = -Werror -Wextra -Wall -g

all: a.out
	./a.out

debug: a.out
	lldb ./a.out

# breakpoint set --file main.c --line 10
# breakpoint set --name main
# breakpoint set --address 0x100000f4
# breakpoint set --function main
# run

a.out: $(wildcard *.c)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f a.out