#include "Game.h"

Game::Game(Deck* d, Player* h, Player* v){ // should deal all cards
    deck = d;
    hero = h;
    villain = v;
    // hero->add_combos(deck);
    // villain->add_combos(deck);
    // deal hands
    hero->hand = hero->possible_hands[hero->player_rng(rng)];
    while (true) {
        villain->hand = villain->possible_hands[villain->player_rng(rng)];
        if (villain->hand[0] == hero->hand[0] || villain->hand[1] == hero->hand[0]
            || villain->hand[1] == hero->hand[1] || villain->hand[1] == hero->hand[1]) continue;
        else break;
    }
    
};

Game::~Game(){
    /*
        re add cards to deck and clear player hands, as well as turn and river
    */
   hero->hand.clear();
   villain->hand.clear();

}