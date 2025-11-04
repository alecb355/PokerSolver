#include "PokerSolver/Game.h"
#include "PokerSolver/Action.h"
#include "PokerSolver/Player.h"
#include <utility>
#include <iostream>
#include <string>
#include <queue>

#define CARDS_DEALT 6


int main(int argc, char** argv){
    // Change lines below to modify player ranges
    std::string hero_range = "AA, AKo, AKs, JTo, KK, KQs";
    std::string villain_range = "AA, AKo, AKs, JTo, KK, KQs";
    Player hero(hero_range);
    Player villain(villain_range);
    Deck deck;
    // std::cout<<"before adding flop\n";
    deck.add_flop(argv[1]);
    std::cout<<"added flop\n";
    hero.add_combos(&deck);
    std::cout<<"added combos\n";
    return 0;
}