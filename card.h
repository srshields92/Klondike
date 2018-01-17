#ifndef GUARD_card
#define GUARD_card

#include <string>
#include "UnicodeCards.h"

// Defines the class for a card of the traditional 52 playing cards
class Card
{
 protected:
  std::string front, back;
  char suit;
  bool isred, faceup;
  int value;
 public:
  Card();
  Card(int, char, bool); // Card(name,suit,faceup), A = 1, J = 11, Q = 12, K = 13
  bool facing_up(void);
  std::string card_image(void);
  std::string card_image(bool);
  void flip(void);
  char get_suit(void);
  int get_value(void);
  bool is_red(void);
};

#endif
