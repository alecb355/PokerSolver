#include "Game.h"

Game::Game(Deck* d, Player* h, Player* v){ // should deal all cards
    deck = d;
    hero = h;
    villain = v;
    // hero->add_combos(deck);
    // villain->add_combos(deck);
    // deal hands
    hero->hand = hero->possible_hands[hero->player_rng(rng)];
    deck->dealt_cards[3] = card_to_int(hero->hand[0]);
    deck->dealt_cards[4] = card_to_int(hero->hand[1]);
    while (true) {
        villain->hand = villain->possible_hands[villain->player_rng(rng)];
        if (villain->hand[0] == hero->hand[0] || villain->hand[1] == hero->hand[0]
            || villain->hand[1] == hero->hand[1] || villain->hand[1] == hero->hand[1]) continue;
        else break;
    }
    deck->dealt_cards[5] = card_to_int(villain->hand[0]);
    deck->dealt_cards[6] = card_to_int(villain->hand[1]);
    turn = deck->deal_card(7);
    river = deck->deal_card(8);
    // everything is set
};

Game::~Game(){
    /*
        re add cards to deck and clear player hands, as well as turn and river
    */
   hero->hand.clear();
   villain->hand.clear();
   for(uint8_t &val: deck->dealt_cards){
        val = 52;
   }
}

void Game::run(){
    // ranges are calculated, hands,turn, river all dealt
    
}