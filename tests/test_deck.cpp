#include "../lib-PokerSolver/Action.h"
#include "../lib-PokerSolver/Game.h"
#include "../lib-PokerSolver/Player.h"
#include "../lib-PokerSolver/Hand_Helpers.h"
#include <utility>
#include <iostream>
#include <string>

int main(int argc, char** argv){
    std::string range = "AA, AKo, AKs, JTo, KK, KQs";
    rng();
    rng();
    Player hero(range);
    Player villain(range);
    Deck deck;
    std::cout<<"adding combos\n";
    hero.add_combos(&deck);
    villain.add_combos(&deck);
    std::cout<<"adding flop\n";
    deck.add_flop("AsTc3d");
    Game game(&deck, &hero, &villain);
    print_hand(hero.hand);
    print_hand(villain.hand);
    std::cout<<"dealt cards: ";
    for(const auto &v: deck.dealt_cards){
        Card temp = int_to_card(v);
        print_card(temp);
        std::cout<<", ";
    }
}