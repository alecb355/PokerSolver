#include "Node.cpp"
#include "Action.cpp"
#include "Hand.cpp"
#include "Deck.cpp"
#include <utility>
#include <iostream>
#include <string>
#include <random>
#include <queue>

#define CARDS_DEALT 6

typedef std::mt19937 my_rng;

std::vector<std::uniform_int_distribution<uint8_t> > distributions; // distributions[0] == [0, 48], [1] = [0, 47], ..

Deck deck;

my_rng rng;

void initialize_program(char *flop){
    deck.add_flop(flop);
    for(int i = 0; i < CARDS_DEALT; ++i){
        distributions.push_back(std::uniform_int_distribution<uint8_t>(0, 48 - i));
    }
}

void game_cleanup(){
    /*
        - reset last 2 cards from board[] <- IS THIS NECESSARY???
        - reset deck to just have flop inputted
        - reset range probilities
    */
}

/* 
    51
    49
    49



*/

void initialize_game(){
    std::uniform_int_distribution<uint8_t> balls(0, 51);
    // std::vector<std::vector<std::string> > range = {{"AA", 5}};
    std::vector<uint8_t> dealt(CARDS_DEALT, 52); // 52 is greater than any possible number received
    for(int i = 0; i < CARDS_DEALT; ++i){
        uint8_t rand = distributions[i](rng);
        if(deck.deck[rand]){
            int j = 52;
            while(deck.deck[--j]);
            
        }
    }


}
void cfr(Node* node, std::vector<Card> &hero_hand, std::vector<Card> &villain_hand, std::vector<Card> &board, double hero_reach, double villain_reach, int street){
    for(const auto &action: node->actions){

    }
}

int main(int argc, char** args){
    /*
        initialize()
            -randomize hero and villain hands, turn, river
        hero_hand
        villain_hand
        board
        Cfr()
    */
    
    return 0;
}// [AA=3, AKs=3, AKo=9, KK=6, QQ=3] flop=QdKdAd
// AA = 0.04 AK = 0.09
// 0.04, 0.13 0.12
/*
    A K Q
  A  
  k
  Q

    ACTION (DEAL)
    
    Node.actions: (FOLD, RAISE, DEAL)
    node.children (null, new Node, NodeJh, Node Ks, Node Ad, )

*/