#ifndef DECK_H
#define DECK_H

#include <vector>
#include <inttypes.h>
#include <string>
#include <random>
#define DECK_SIZE 52
#define RANKS 13
#define SUITS 4

/*
    RANKS: 0-12 where 0 is deuce, 12 is A
    SUITS: 0-3, in order: clubs, diamonds, hearts, spades
*/

typedef std::mt19937 my_rng;
// std::random_device rd;
static my_rng rng;

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
    std::vector<Card> board;
    std::vector<uint8_t> dealt_cards;
    
    std::uniform_int_distribution<uint8_t>* deck_distribution;

    //uint8_t is only 1 byte for int instead of normal 4 (more efficient).
    void add_flop(char* flop);

    Card deal_card(const int &dealt_idx);

    ~Deck();
};

uint8_t card_to_int(const Card &c);

Card int_to_card(const uint8_t &val);

uint8_t parse_rank(const char &r);


#endif