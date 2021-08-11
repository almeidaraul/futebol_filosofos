CFLAGS = -Wall -O3
LDLIBS = -l hireds -l readline

all: main

gcc:
	gcc main.cpp util.cpp campo.c $(CFLAGS) $(LDLIBS) -o futebas

gpp:
	g++ main.cpp util.cpp campo.c $(CFLAGS) $(LDLIBS) -o futebas

main:
	g++ main.cpp util.cpp campo.c $(CFLAGS) $(LDLIBS) -o futebas

test: main
	./futebas < in.txt
