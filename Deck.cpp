#include "Deck.h"

Deck::Deck(){
    deck.resize(52, 1);
    size = 52;
}

uint8_t Deck::card_to_suit(const uint8_t &card){
    return card/13;  // 0-12 = 0, 13-25 = 1 ...
}

uint8_t Deck::card_to_rank(const uint8_t &card){
    return card%13; // 0-12 = 0-12, 13-25 = 0-12 ...
}

Card::Card(int r, int s): rank(r), suit(s) {}

/*
    Node{
        hand
        pot
        actions
        children[NUM_ACTIONS]
    }
    node[action] == nullptr
    if(action== bet || raise){
        node[bet][ammount] == nullptr
    }

    cfr(pair<int, int>& p1_hand, pair<int, int>& p2_hand, Node& node) // per node
    map<string, node>
    string = "AhTs.3c.10s"
    node = map["AhTs.3c.10s"] 
    node.action_history
    while(train){
        AhAcAs
        AhAcAs
    
    }


*/
