#ifndef DECK_H
#define DECK_H

#include <vector>
#include <inttypes.h>
#include <string>
#define DECK_SIZE 52
#define RANKS 13
#define SUITS 4

/*
    RANKS: 0-12 where 0 is deuce, 12 is A
    SUITS: 0-3, in order: clubs, diamonds, hearts, spades
*/
class Card{
    public:
    unsigned int rank: 4;
    unsigned int suit: 2;
    Card();
    Card(int r, int s);
    
    bool operator==(const Card&) const;
};

class Deck{
    public:
    Deck();
    std::vector<bool> deck;
    std::vector<Card> board;

    //uint8_t is only 1 byte for int instead of normal 4 (more efficient).
    void add_flop(char* flop);

    uint8_t card_to_suit(const uint8_t &card);

    uint8_t card_to_rank(const uint8_t &card);
};


#endif