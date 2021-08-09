CFLAGS = -Wall -O3

all: main

main:
	g++ main.cpp util.cpp $(CFLAGS) -o futebas

test: main
	./futebas < in.txt
