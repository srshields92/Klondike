#include <string>
#include "UnicodeCards.h"
#include "card.h"

Card::Card(void)
{
  value = 1;
  suit = 'S';
  faceup = true;
}

Card::Card(int value_in, char suit_in, bool faceup_in)
{
  value = value_in;
  suit = suit_in;
  faceup = faceup_in;

  switch(suit)
  {
  case 'S': front = SPADES[value-1];
    isred = false;
    break;
  case 'H': front = HEARTS[value-1];
    isred = true;
    break;
  case 'D': front = DIAMONDS[value-1];
    isred = true;
    break;
  case 'C': front = CLUBS[value-1];
    isred = false;
    break;
  }
  back = "\033[1;31;47m\U0001F0A0\033[0m";


}

bool Card::facing_up(void)
{
  return faceup;
}

std::string Card::card_image(void)
{
  if(faceup)
    {
      return front;
    }
  else
    {
      return back;
    }
}

std::string Card::card_image(bool isfaceup)
{
  if(isfaceup)
    {
      return front;
    }
  else
    {
      return back;
    }
}

void Card::flip(void)
{
  if(faceup)
    {
      faceup = false;
    }
  else
    {
      faceup = true;
    }
}

char Card::get_suit(void)
{
  return suit;
}

int Card::get_value(void)
{
  return value;
}

bool Card::is_red(void)
{
  if(suit == 'D' || suit == 'H')
    {
      return true;
    }
  else
    {
      return false;
    }
}
