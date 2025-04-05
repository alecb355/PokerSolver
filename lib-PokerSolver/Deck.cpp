#include "Deck.h"
#include <cassert>
#include <iostream>

Deck::Deck(){
    board.resize(5);
    dealt_cards.resize(52, 52);
    deck_distribution = (std::uniform_int_distribution<int>(0, 51));
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
        // std::cout<<"idx: "<<board_idx<<", val: "<<(rank + (13 * (suit)))<<"\n";
        dealt_cards[board_idx] = (rank + (13 * (suit)));
        board[board_idx].rank = rank;
        board[board_idx].suit = suit;
    }
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
        uint8_t rnd = (deck_distribution)(rng);
        bool is_valid = true;
        for(const uint8_t &val: dealt_cards){
            if(val == rnd){
                is_valid = false;
                break;
            }
        }
        if(is_valid){
            dealt_cards[dealt_idx] = rnd;
            return int_to_card(rnd);
        }
    }
}

Card::Card(): rank(15), suit(3) {}

Card::Card(int r, int s): rank(r), suit(s) {}

bool Card::operator==(const Card& rhs) const{
    return (rank == rhs.rank && suit == rhs.suit);
}

Deck::~Deck(){
    // delete deck_distribution;
}
