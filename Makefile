CFLAGS = -Wall -O3
LDLIBS = -l hiredis -l readline

all: main

exec: all
	./futebas e

main:
	gcc $(CFLAGS) $(LDLIBS) -c -o campo.o campo.c
	g++ -c -o main.o main.cpp $(CFLAGS) $(LDLIBS)
	g++ -c -o util.o util.cpp $(CFLAGS) $(LDLIBS)
	g++ -o futebas campo.o main.o util.o $(CFLAGS) $(LDLIBS)

test: main
	./futebas < in.txt
