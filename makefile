all: witsshell
witsshell: witsshell.c
	gcc witsshell.c -Wall -Wextra -pedantic -o witsshell
clean:
	rm -f witsshell