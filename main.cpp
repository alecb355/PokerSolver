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

std::vector<std::vector<uint8_t>> combos_left(13, std::vector<uint8_t>(13, 0)); //j>i => suited
std::vector<std::vector<uint8_t>> hero_range(3, std::vector<uint8_t>(2,0));
std::vector<std::vector<uint8_t>> villain_range(3, std::vector<uint8_t>(2,0));
std::vector<std::vector<Card>> hero_hands(1176, std::vector<Card>(2, Card())); //1176 = 49 choose 2
std::vector<std::vector<Card>> villain_hands(1176, std::vector<Card>(2, Card())); //1176 = 49 choose 2
int num_hero_hands = 0;
int num_villain_hands = 0;

std::uniform_int_distribution<int> hero_rng;
std::uniform_int_distribution<int> villain_rng;

Deck deck;

my_rng rng;

void initialize_program(char *flop){
    deck.add_flop(flop);
    for(int i = 0; i < CARDS_DEALT; ++i){
        distributions.push_back(std::uniform_int_distribution<uint8_t>(0, 48 - i));
    }

    hero_range[1][1] = 1; //aks
    hero_range[2][0] = 1; //ako

    //OTHER WAY OF DOING IT HERE:
    //first we want to create a vector for all hero exact combos (eg Ah5h) (resp. villain)
    for (int k = 0; k < hero_range.size(); k++) { // (11,12) (12,12) (12,11)
        uint8_t i = hero_range[k][0];
        uint8_t j = hero_range[k][1];

        if (i == j) { //add pairs
            std::vector<uint8_t> suits_spanned(4,0);
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 3; first++) { //now add the actual combos
                for (int second = first+1; second < 4; second++) {
                    if (suits_spanned[first] == 0 && suits_spanned[second] == 0) {
                        Card c1(i, first);
                        Card c2(i, second);
                        std::vector<Card> hand = {c1,c2};
                        hero_hands[num_hero_hands] = hand;
                        num_hero_hands++;
                    }
                }
            }
        } else if (j > i) { //add suited combos
            std::vector<uint8_t> suits_spanned(4,0);
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i || c.rank == j) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 4; first++) { //add combos
                if (suits_spanned[first] == 0) {
                    Card c1(i, first);
                    Card c2(j, first);
                    std::vector<Card> hand = {c1,c2};
                    hero_hands[num_hero_hands] = hand;
                    num_hero_hands++;
                }
            }
        } else { //add offsuit combos (i>j)
            std::vector<uint8_t> first_suits_spanned(4,0); //suits spanned for cards of rank i
            std::vector<uint8_t> second_suits_spanned(4,0); //suits spanned for cards of rank j
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i) {
                    first_suits_spanned[c.suit] = 1;
                } else if (c.rank == j) {
                    second_suits_spanned[c.suit] = 1;
                }
            }

            for (int first = 0; first<4; first++) {
                for (int second = 0; second<4; second++) {
                    if (first_suits_spanned[first] == 0 && second_suits_spanned[second] == 0) {
                        Card c1(i, first);
                        Card c2(j, second);
                        std::vector<Card> hand = {c1,c2};
                        hero_hands[num_hero_hands] = hand;
                        num_hero_hands++;
                    }
                }
            }
        }
    }
    hero_rng = std::uniform_int_distribution<int>(0, num_hero_hands-1);

    for (int k = 0; k < villain_range.size(); k++) { //now add villain combos
        uint8_t i = villain_range[k][0];
        uint8_t j = villain_range[k][1];

        if (i == j) { //add pairs
            std::vector<uint8_t> suits_spanned(4,0);
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 3; first++) { //now add the actual combos
                for (int second = first+1; second < 4; second++) {
                    if (suits_spanned[first] == 0 && suits_spanned[second] == 0) {
                        Card c1(i, first);
                        Card c2(i, second);
                        std::vector<Card> hand = {c1,c2};
                        villain_hands[num_villain_hands] = hand;
                        num_villain_hands++;
                    }
                }
            }
        } else if (j > i) { //add suited combos
            std::vector<uint8_t> suits_spanned(4,0);
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i || c.rank == j) {
                    suits_spanned[c.suit] = 1;
                }
            }
            
            for (int first = 0; first < 4; first++) { //add combos
                if (suits_spanned[first] == 0) {
                    Card c1(i, first);
                    Card c2(j, first);
                    std::vector<Card> hand = {c1,c2};
                    villain_hands[num_villain_hands] = hand;
                    num_villain_hands++;
                }
            }
        } else { //add offsuit combos (i>j)
            std::vector<uint8_t> first_suits_spanned(4,0); //suits spanned for cards of rank i
            std::vector<uint8_t> second_suits_spanned(4,0); //suits spanned for cards of rank j
            for (Card c : deck.board){ //set suits spanned
                if (c.rank == i) {
                    first_suits_spanned[c.suit] = 1;
                } else if (c.rank == j) {
                    second_suits_spanned[c.suit] = 1;
                }
            }

            for (int first = 0; first<4; first++) {
                for (int second = 0; second<4; second++) {
                    if (first_suits_spanned[first] == 0 && second_suits_spanned[second] == 0) {
                        Card c1(i, first);
                        Card c2(j, second);
                        std::vector<Card> hand = {c1,c2};
                        villain_hands[num_villain_hands] = hand;
                        num_villain_hands++;
                    }
                }
            }
        }
    }
    villain_rng = std::uniform_int_distribution<int>(0, num_villain_hands-1);
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

    std::vector<Card> hero_hand = hero_hands[hero_rng(rng)];
    std::vector<Card> villain_hand;
    while (true) {
        villain_hand = villain_hands[villain_rng(rng)];
        if (villain_hand[0] == hero_hand[0] || villain_hand[1] == hero_hand[0]
            || villain_hand[1] == hero_hand[1] || villain_hand[1] == hero_hand[1]) continue;
        else break;
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