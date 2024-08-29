#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include <vector>
#include <string>

#define DEFAULT_STACK 100.0

class Player{
    public:
    std::vector<Card> hand;
    double stack;
    std::vector<std::vector<Card>> possible_hands;
    std::vector<std::vector<uint8_t>> range;
    std::uniform_int_distribution<int> player_rng;
    // add strategies here
    Player(std::string range_str);
    void add_combos(Deck* deck);
};


#endif