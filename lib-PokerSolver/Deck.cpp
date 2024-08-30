#include "Deck.h"
#include <cassert>
#include <iostream>

Deck::Deck(){
    board.resize(5);
    dealt_cards.resize(9, 52);
    deck_distribution = new std::uniform_int_distribution<uint8_t>(0, 51);
}

void Deck::add_flop(char* flop){
    // std::cout<<"FLOP SIZE: "<<sizeof(flop)<<"\n";
    // std::cout<<flop[6]<<" "<<flop[7]<<"\n";
    // assert(sizeof(flop) == 6); // example flop input: AdTc4s which has size 6
    int rank = 0, suit = 0;
    int board_idx = 0;
    for(int i = 0; i < 5; i += 2, board_idx++){
        char r = flop[i];
        char s = flop[i+1];
        rank = parse_rank(r); // ranks are like this for indexing purposes
         // '2' - '0' = 2, but deuce is 1 here (for indexing purposes)
        // parse suit
        if(s == 'c') suit = 0;
        else if(s == 'd') suit = 1;
        else if(s == 'h') suit = 2;
        else suit = 3; // if we get weird value for suit gg
        dealt_cards[board_idx] = (rank + (13 * (suit)));
        board[board_idx].rank = rank;
        board[board_idx].suit = suit;
    }
    std::cout<<"exiting add_flop\n";
}
uint8_t parse_rank(const char &r){
    if(r == 'A') return 12;
    else if(r == 'K') return 11;
    else if(r == 'Q') return 10;
    else if(r == 'J') return 9;
    else if(r == 'T') return 8;
    else return (r - '0' - 2);
}

uint8_t card_to_int(const Card &c){
    return c.rank + (13 * (c.suit)); 
}

Card int_to_card(const uint8_t &val){
    int rank = val % 13;
    int suit = val / 13;
    return Card(rank, suit);
}

Card Deck::deal_card(const int &dealt_idx){
    while (true) {
        uint8_t temp = (*(deck_distribution))(rng);
        bool is_valid = true;
        for(const uint8_t &val: dealt_cards){
            if(val == temp){
                is_valid = false;
                break;
            }
        }
        if(is_valid){
            dealt_cards[dealt_idx] = temp;
            return int_to_card(temp);
        }
    }
}

Card::Card(): rank(15), suit(3) {}

Card::Card(int r, int s): rank(r), suit(s) {}

bool Card::operator==(const Card& rhs) const{
    return (rank == rhs.rank && suit == rhs.suit);
}

Deck::~Deck(){
    delete deck_distribution;
}
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
