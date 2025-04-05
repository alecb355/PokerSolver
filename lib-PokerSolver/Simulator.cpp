#include "Simulator.h"
#include "Game.h"
#include <iostream>

Simulator::Simulator(char* flop, std::string hero_range, std::string villain_range, bool first){
    first_to_act = first;
    deck = new Deck();
    deck->add_flop(flop);

    hero = new Player(hero_range);
    villain = new Player(villain_range);

    hero->add_combos(deck);
    villain->add_combos(deck);

    idx_to_turn_card.resize(NUM_CARD_NODES);
    idx_to_river_card.resize(NUM_CARD_NODES, std::vector<Card>(NUM_CARD_NODES));

    // initialize tree here?
    initialize_tree();
}

void Simulator::initialize_tree(){
    // pre-select turns and rivers
    for(int i = 0; i < NUM_CARD_NODES; ++i){
        idx_to_turn_card[i] = deck->deal_card(i+3);
        for(int j = 0; j < NUM_CARD_NODES; ++j){
            idx_to_river_card[i][j] = deck->deal_card(i+4+j);
        }
        for(int j = 0; j < NUM_CARD_NODES; ++j){
            deck->dealt_cards[i+4+j] = 52;
        }
    }
    for(int i = 0; i < NUM_CARD_NODES; ++i){
        deck->dealt_cards[i+3] = 52;
    }
}

void Simulator::run(int num_iterations){
    // hero always starts first
    if(!first_to_act) std::swap(hero, villain); // in game call, hero always goes first
    while(num_iterations--){
        Game game(deck, hero, villain);
    }
}

void traverse_delete(Node* node){
    if(!node) return;
    for(int i = 0; i < NUM_CARD_NODES; ++i){
        traverse_delete(node->card_nodes[i]);
    }
    for(int i = 0; i < NUM_RAISE_NODES; ++i){
        traverse_delete(node->raise_nodes[i]);
    }
    delete node;
}

Simulator::~Simulator(){
    delete hero;
    delete villain;
    delete deck;
    // TODO: traverse_delete(root);
}