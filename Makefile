# Makefile for C++ application: "Card game Suite"
# created by Sidney Shields 01/17/2018

PROG = card_game_suite
CC = g++
CPPFLAGS = -g -Wall -I./headers
LDFLAGS = -L./source
OBJS = main.o deck.o card.o Klondike.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c ./source/main.cpp
deck.o :
	$(CC) $(CPPFLAGS) -c ./source/deck.cpp
card.o :
	$(CC) $(CPPFLAGS) -c ./source/card.cpp
Klondike.o :
	$(CC) $(CPPFLAGS) -c ./source/Klondike.cpp
clean:
	rm -f core $(OBJS)
