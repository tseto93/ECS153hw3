all: runpriv sniff

runpriv: runpriv.c
	gcc -Wall -o runpriv runpriv.c

sniff: sniff.c
	gcc -Wall -o sniff sniff.c
