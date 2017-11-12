bin: conv.c
	gcc conv.c -o conv

install: bin
	cp conv /usr/bin/
