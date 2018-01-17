#ifndef GUARD_Klondike
#define GUARD_Klondike
// Header file for the Klondike solitare game

#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "deck.h"

class Stack:public Deck
{
 public:
  Stack();
  Stack(std::vector<Card>);
  std::string display(void);   // returns the string as needed for the game (just top card)
  std::string display(std::string); // gives an alternate display if stack is empty
};

void moveCards(Deck[], Stack&, int, int, int);  // moves a list of cards from one list to another in the game
                                          //(amount, start, destination)
void dealCards(Deck[], Stack&);
bool canMove(Deck[], Stack&, int, int, int);    // Determines if a list of cards can be moved
                                          //(amout, start, destination)
void restack(Stack&, Stack&);     // moves the discard stack to the main stack
void rapture(Deck[], Deck[], Stack&, int); // determines if a card can be 'raptured' from a list then 'raptures' it
bool gameOver(Stack[]);        // Determines if the game is over by checking the 4 victory stacks
void displayGame(Deck[],Stack[],Stack&,Stack&);
void Klondike(void);          // plays the game


#endif
