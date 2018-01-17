#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "Klondike.h"

Stack::Stack()
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

Stack::Stack(std::vector<Card> cards)
{
  cards_in_deck = cards;
  deck_size = cards.size();
}

std::string Stack::display(void)
{
  if(deck_size)
  {
    Card top_card = get_top_card();
    return top_card.card_image();
  }
  else
  {
    return "\033[1;31;47m\U0001F0DF\033[0m";
  }
}

std::string Stack::display(std::string emptyStack)
{
  if(deck_size)
    {
      Card top_card = get_top_card();
      return top_card.card_image();
    }
  else
    {
      return emptyStack;
    }
}

void moveCards(Deck gameLists[], Stack& discard, int amount, int target, int destination)
// moves a list of cards from one list to another in the game
{
  std::vector<Card> emptyVec;
  Stack temp_card_stack(emptyVec);
  // Move the cards into a temporary stack
  if(target == 8)
    {
      temp_card_stack.add_card(discard.draw_card());
    }
  else if(target <=7 && target >=1)
    {
      for(int i = 0; i < amount; i++)
        {
          temp_card_stack.add_card(gameLists[target-1].draw_card());
        }
    }
  // Now move cards to their destination
  for(int i = 0; i < amount; i++)
    {
      gameLists[destination-1].add_card(temp_card_stack.draw_card());
    }
}

void dealCards(Deck gameLists[], Stack& deal)
{
  Stack starter_deck;
  starter_deck.shuffle();
  for(int i = 0; i < 7; i++)
    {
      for(int j = 0; j < i + 1; j++)
        {
          gameLists[i].add_card(starter_deck.draw_card());
        }
      gameLists[i].flip_top_card();
    }
  deal = starter_deck;
}


bool canMove(Deck gameLists[], Stack& discard, int amount, int target, int destination)
// Determines if a list of cards can be moved
{
  // Test if we are trying to move empty cards first:
  if(target == 8 && discard.cards_in_deck.empty()) // drawing from discard
    {
      return false;
    }
  else if(target <= 7 && target >= 1)
    {
      if(gameLists[target-1].cards_in_deck.empty())
        {
          return false;
        }
    }

  // Test if we are trying to move more cards than we are allowed:
  if(target == 8 && amount > 1)
    {
      return false;
    }
  else if(target <=7 && target >=1 && gameLists[target-1].amount_faceup() < amount)
    {
      return false;
    }

  // Extract the top of the pile we are moving
  Card top_of_move_pile;
  if(target == 8)
    {
      top_of_move_pile = discard.get_top_card();
    }
  else if(target <=7 && target >=1)
    {
      top_of_move_pile = gameLists[target-1].cards_in_deck[gameLists[target-1].get_deck_size() - amount];
    }

  // Determine if the stack can be moved
  if(top_of_move_pile.get_value() == 13 && gameLists[destination - 1].cards_in_deck.empty())
    { // if we are moving to a blank space it must be a king.
        return true;
    }
  else if(gameLists[destination - 1].cards_in_deck.empty())
    { // otherwise, if the space is blank, we can't move
      return false;
    }
  Card destinationCard = gameLists[destination - 1].get_top_card();
  if((top_of_move_pile.is_red() != destinationCard.is_red())
       && (top_of_move_pile.get_value() == destinationCard.get_value() -1))
    {
      return true;
    }
  // Otherwise, if we get here without returning something, return false
  return false;
}


void restack(Stack& deal, Stack& discard)   // moves the discard stack to the main stack
{
  while(!discard.cards_in_deck.empty())
    {
      discard.flip_top_card();
      deal.add_card(discard.draw_card());
    }
}

void rapture(Deck gameLists[], Deck victoryLists[], Stack& discard, int listChoice)
// determines if a card can be 'raptured' from a list then 'raptures' it
{
  Card rapture_card;
  if(listChoice == 8)
    {
      rapture_card = discard.get_top_card();
    }
  else if(listChoice <= 7 && listChoice >= 0)
    {
      rapture_card = gameLists[listChoice-1].get_top_card();
    }
  char suit = rapture_card.get_suit();
  int value = rapture_card.get_value();

  // change suit to numbers to index victoryLists array
  int suit_num;
  switch(suit)
    {
    case 'S': suit_num = 0; break;
    case 'H': suit_num = 1; break;
    case 'D': suit_num = 2; break;
    case 'C': suit_num = 3; break;
    }

  int top_card_value = 0;
  if(!victoryLists[suit_num].cards_in_deck.empty())
    {
      Card top_card = victoryLists[suit_num].get_top_card();
      top_card_value = top_card.get_value();
    }
  if(top_card_value == value - 1)
    {
      if(listChoice == 8)
        {
          victoryLists[suit_num].add_card(discard.draw_card());
        }
      else
        {
          victoryLists[suit_num].add_card(gameLists[listChoice-1].draw_card());
        }
    }

}

bool gameOver(Stack victoryLists[])        // Determines if the game is over by checking the 4 victory stacks
{
  bool endgame = true;

  for(int i = 0; i < 4; i++)
    {
      if(victoryLists[i].cards_in_deck.empty())
        {
          return false;
        }
      Card top_card = victoryLists[i].get_top_card();
      if(top_card.get_value() != 13)
        {
          endgame = false;
        }
    }
  return endgame;
}

void displayGame(Deck gameLists[],Stack victoryLists[],Stack& deal,Stack& discard)
// (game lists, victory lists, dealing stack, discard stack)
{
  // Clear the buffer
  std::cout << "\033[2J\033[1;1H";
  // Display deck, discard, and victory stacks
  std::cout << deal.display() << discard.display() << "  "
            << victoryLists[0].display("\033[1;30;47m\u2664\033[0m")
            << victoryLists[1].display("\033[1;31;47m\u2661\033[0m")
            << victoryLists[2].display("\033[1;31;47m\u2662\033[0m")
            << victoryLists[3].display("\033[1;30;47m\u2667\033[0m") << std::endl;
  // Find maximum list size:
  int max = 0;
  for(int i = 0; i < 7; i++)
    {
      if(gameLists[i].get_deck_size() > max);
      {
        max = gameLists[i].get_deck_size();
      }
    }
  std::cout << " 1234567" << std::endl;
  // Display lists of cards for the game
  for(int i = 0; i < max; i++)
    {
      std::cout << " ";
      for(int j = 0; j < 7; j++)
        {
          if(i+1 > gameLists[j].cards_in_deck.size())
            {
              std::cout << " ";
            }
          else
            {
              std::cout << gameLists[j].cards_in_deck[i].card_image();
            }
        }
      std::cout << std::endl;
    }
  std::cout << std::endl;
}


void Klondike(void)          // plays the game
{
  std::vector<Card> emptyVec;
  Stack deal;
  Stack discard(emptyVec);
  Stack spades(emptyVec), hearts(emptyVec), diamonds(emptyVec), clubs(emptyVec);
  Stack victoryStacks[4] = {spades, hearts, diamonds, clubs};
  Deck list1(emptyVec), list2(emptyVec), list3(emptyVec), list4(emptyVec), list5(emptyVec),
    list6(emptyVec), list7(emptyVec);
  Deck gameLists[7] = {list1,list2,list3,list4,list5,list6,list7};
  dealCards(gameLists, deal);
  // Master game loop
  while(true)
  {
    displayGame(gameLists,victoryStacks,deal,discard);
    int numCards = 1;
    std::string choice1, choice2;
    std::vector<std::string> listChoices = {"1","2","3","4","5","6","7"};
    std::cout << "Please select a stack to move from (1-7), select card from discard (8),"
              << " (d)raw a card, or (e)xit the game: ";
    std::cin >> choice1;
    if(choice1 == "e") { break; } // exit the game
    else if(choice1 == "d")
      {
        if(!deal.cards_in_deck.empty())
          {
            deal.flip_top_card();
            discard.add_card(deal.draw_card());
          }
        else
          {
            restack(deal,discard);
          }
      }
    else // if not "e" or "d"
      {
        if(std::find(listChoices.begin(), listChoices.end(), choice1) != listChoices.end())
          {
            std::cout << "How many cards?: ";
            std::cin >> numCards;
          }
        std::cout <<"Please select a stack to move to (1-7), (r)apture to the victory stacks, or (e)xit the game: ";
        std::cin >> choice2;
        if(choice2 == "e") { break; } // exit the game

        // implement rapturing
        if(choice2 == "r")
          {
            if(std::find(listChoices.begin(), listChoices.end(), choice1) != listChoices.end() || choice1 == "8")
              {
                rapture(gameLists, victoryStacks, discard, stoi(choice1));
              }
          }
        // implement moving stacks
        else if(canMove(gameLists,discard,numCards,stoi(choice1),stoi(choice2)))
          {
            moveCards(gameLists,discard,numCards,stoi(choice1),stoi(choice2));
          }
      }

    // implement flipping card
    for(int i = 0; i < 7; i++)
      {
        if(gameLists[i].cards_in_deck.empty()) { break; }
        if(!gameLists[i].top_card_is_up())
          {
            gameLists[i].flip_top_card();
          }
      }

    // implement win condition
    if(gameOver(victoryStacks))
      {
        std::cout << "Game over, you win!" << std::endl;
        break;
      }
  }
}


