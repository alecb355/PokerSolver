#include "../lib-PokerSolver/Action.h"
#include "../lib-PokerSolver/Game.h"
#include "../lib-PokerSolver/Player.h"
#include "../lib-PokerSolver/Hand_Helpers.h"
#include <utility>
#include <iostream>
#include <string>

int main(int argc, char** args){
    std::string range = "AA, AKo, AKs, JTo, KK, KQs";
    Player hero(range);
    std::cout<<"RANGE: "<<"\n";
    for(auto &v: hero.range){
        int i = v[0];
        int j = v[1];
        std::cout<<i<<" "<<j<<"\n";
    }
    std::cout<<"done adding range\n";
    Player villain(range);
    Deck deck;
    deck.add_flop("AsAcAd");
    hero.add_combos(&deck);
    villain.add_combos(&deck);
    std::cout<<"printing hero possible hands: ";
    for(auto &h: hero.possible_hands){
        print_hand(h);
    }
    std::cout<<"printing villain possible hands: ";
    for(auto &h: villain.possible_hands){
        print_hand(h);
    }
    Game game(&deck, &hero, &villain);
    std::cout<<"Hero's hand: ";
    print_hand(hero.hand);
    std::cout<<"random numbers: ";
    for(int i = 0; i < 10; ++i){
        int temp = hero.player_rng(rng);
        std::cout<<temp<<" ";
    }
    // hero.hand = hero.possible_hands[hero.player_rng(rng)];
    // print_hand(hero.hand);
    // hero.hand = hero.possible_hands[hero.player_rng(rng)];
    // print_hand(hero.hand);
    std::cout<<"Villain's hand: ";
    print_hand(villain.hand);
}