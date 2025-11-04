#include "PokerSolver/Simulator.h"
#include "PokerSolver/Game.h"
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

    root = new Node();
    traverse_create(root, 0, 0);
}

/*
    Table on count (with NUM_CARD_NODES = 7):

    street_limit  bet_count_limit   count
    1               1               ~450
    1               2               ~22000
    2               1               ~25000
    2               2                >6,100,000 (at least 20 seconds)


*/

/*
    Table on count (with NUM_CARD_NODES = 5):

    street_limit  bet_count_limit   count
    1               1               
    1               2               
    2               1                ~13000
    2               2                ~4,600,000 (15-ish seconds)


*/

const int BET_COUNT_LIMIT = 2;

// int count = 0;

// Street value of 0 is flop, 1 is turn, 2 is river
// BET_COUNT_LIMIT is just to limit the amount of raise and re-raising so the game_tree doesn't grow stupidly fast
void traverse_create(Node* node, const int &street, const int &bet_count){
    // std::cout<<"Count: "<<count++<<"\n";
    // No need to create card nodes on river
    if(street < 2){
        for(int i = 0; i < NUM_CARD_NODES; ++i){
            Node* new_node = new Node();
            node->card_nodes.push_back(new_node);
            // next street, starts with no bets.
            traverse_create(node->card_nodes[i], street + 1, 0);
        }
    }
    // No more than 4-betting per street
    if(bet_count < BET_COUNT_LIMIT){
        for(int i = 0; i < NUM_RAISE_NODES; ++i){
            Node* new_node = new Node();
            node->raise_nodes.push_back(new_node);
            // same street, bet_count is increased by 1 because of the raise
            traverse_create(node->raise_nodes[i], street, bet_count + 1);
        }
    }
}

void traverse_delete(Node* node){
    if(!node) return;
    for(int i = 0; i < node->card_nodes.size(); ++i){
        traverse_delete(node->card_nodes[i]);
    }
    for(int i = 0; i < node->raise_nodes.size(); ++i){
        traverse_delete(node->raise_nodes[i]);
    }
    delete node;
}


void Simulator::run(int num_iterations){
    // hero always starts first
    if(!first_to_act) std::swap(hero, villain); // in game call, hero always goes first
    while(num_iterations--){
        Game game(deck, hero, villain);
    }
}

Simulator::~Simulator(){
    delete hero;
    delete villain;
    delete deck;
    traverse_delete(root);
}