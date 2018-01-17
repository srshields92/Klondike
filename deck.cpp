#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "card.h"
#include "UnicodeCards.h"
#include "deck.h"

Deck::Deck()
{
  char suit;
  int value;
  cards_in_deck.clear();
  for(int i = 0; i < 4; i++)
    {
      switch(i) // Determine the suit
        {
        case 0: suit = 'S';
          break;
        case 1: suit = 'H';
          break;
        case 2: suit = 'D';
          break;
        case 3: suit = 'C';
          break;
        }
      for(int j = 0; j < 13; j++)
        { // Determine the value
          value = j + 1;
          // Make the card now and add it to the list of cards for the deck
          cards_in_deck.push_back(Card(value,suit,false));
        }
    }
  deck_size = cards_in_deck.size();
}


Deck::Deck(std::vector<Card> cards)
{
  cards_in_deck = cards;
  deck_size = cards.size();
}


Card Deck::get_top_card(void)
{
  return cards_in_deck.back();
}

void Deck::print_cards(void)
{
  if(deck_size)
    {
      for(int i = 0; i < deck_size; i++)
        {
          std::cout << cards_in_deck[i].card_image() << std::endl;
        }
    }
  else
    {
      std::cout << " " << std::endl;
    }
}

void Deck::print_cards(bool faceup)
{
  if(deck_size)
  {
    for(int i = 0; i < deck_size; i++)
      {
        std::cout << cards_in_deck[i].card_image(faceup) << std::endl;
      }
  }
  else
  {
    std::cout << " " << std::endl;
  }
}

int Deck::get_deck_size(void)
{
  return deck_size;
}

void Deck::shuffle(void)
{
  std::random_shuffle(cards_in_deck.begin(), cards_in_deck.end());
}

Card Deck::draw_card(void)
{
  Card top_card = get_top_card();
  cards_in_deck.pop_back();
  deck_size--;
  return top_card;
}

void Deck::add_card(Card card)
{
  cards_in_deck.push_back(card);
  deck_size++;
}

void Deck::flip_top_card(void)
{
  Card top_card = cards_in_deck.back();
  top_card.flip();
  cards_in_deck.back() = top_card;
}

bool Deck::top_card_is_up(void)
{
  Card top_card = cards_in_deck.back();
  return top_card.facing_up();
}

int Deck::amount_faceup(void)
{
  int count = 0;
  for(int i = 0; i < cards_in_deck.size(); i++)
    {
      if(cards_in_deck[i].facing_up())
        {
          count++;
        }
    }
  return count;
}

