#include "../lib-PokerSolver/Game.h"
#include "../lib-PokerSolver/Action.h"
#include "../lib-PokerSolver/Player.h"
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
    deck.add_flop(argv[2]);
    hero.add_combos(&deck);
    
    return 0;
}