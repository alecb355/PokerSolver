#include "Simulator.h"
#include "Game.h"

Simulator::Simulator(char* flop, std::string hero_range, std::string villain_range, bool first){
    first_to_act = first;
    deck = new Deck();
    deck->add_flop(flop);

    hero = new Player(hero_range);
    villain = new Player(villain_range);

    hero->add_combos(deck);
    villain->add_combos(deck);
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
    traverse_delete(node->check_call_node);
    for(int i = 0; i < node->raise_nodes.size(); ++i){
        traverse_delete(node->check_call_node);
    }
    delete node;
}

Simulator::~Simulator(){
    delete hero;
    delete villain;
    delete deck;
    traverse_delete(root);
}