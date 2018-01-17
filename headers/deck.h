#ifndef GUARD_deck
#define GUARD_deck
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "card.h"
#include "UnicodeCards.h"

// Defines a class for a deck/stack of cards where the cards class is defined in card.h
class Deck
{
 protected:
  int deck_size;
 public:
  std::vector<Card> cards_in_deck;
  Deck();                        // initialize with an empty deck
  Deck(std::vector<Card>);       // initialize with given cards
  Card get_top_card(void);
  void print_cards(void);            // print the contents of the deck as is
  void print_cards(bool);        // print the contents of the deck face up or face down
  int get_deck_size(void);
  void shuffle(void);
  Card draw_card(void);
  void add_card(Card);
  void flip_top_card(void);
  bool top_card_is_up(void);
  int amount_faceup(void);
};


#endif
