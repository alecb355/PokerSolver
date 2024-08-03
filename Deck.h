#ifndef DECK_H
#define DECK_H

#include <vector>
#include <inttypes.h>
#define DECK_SIZE 52;
#define SUITS 4;

class Deck{
    private:
    uint8_t size;
    std::vector<bool> deck;
    public:
    Deck();

    //uint8_t is only 1 byte for int instead of normal 4 (more efficient).
    uint8_t card_to_suit(const uint8_t &card);

    uint8_t card_to_rank(const uint8_t &card);

    uint8_t deal();
};

#endif;