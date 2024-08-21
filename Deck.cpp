#include "Deck.h"
#include <cassert>

Deck::Deck(){
    deck.resize(52, 0);
    board.resize(5);
}

void Deck::add_flop(char* flop){
    assert(sizeof(flop) == 6); // example flop input: AdTc4s which has size 6
    int rank = 0, suit = 0;
    int board_idx = 0;
    for(int i = 0; i < 5; i += 2, board_idx++){
        char r = flop[i];
        char s = flop[i+1];
        // parse rank
        if(r == 'A') rank = 13; // ranks are like this for indexing purposes
        else if(r == 'K') rank = 12;
        else if(r == 'Q') rank = 11;
        else if(r == 'J') rank =10;
        else if(r == 'T') rank = 9;
        else rank = (r - '0' - 1); // '2' - '0' = 2, but deuce is 1 here (for indexing purposes)
        // parse suit
        if(s == 'c') suit = 0;
        else if(s == 'd') suit = 1;
        else if(s == 'h') suit = 2;
        else suit = 3; // if we get weird value for suit gg
        deck[(rank * (suit + 1) - 1)] = 1;
        board[board_idx].rank = rank - 1;
        board[board_idx].suit = suit;
    }
}

uint8_t Deck::card_to_suit(const uint8_t &card){
    return card/13;  // 0-12 = 0, 13-25 = 1 ...
}

uint8_t Deck::card_to_rank(const uint8_t &card){
    return card%13; // 0-12 = 0-12, 13-25 = 0-12 ...
}

Card::Card(): rank(15), suit(3) {}

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
